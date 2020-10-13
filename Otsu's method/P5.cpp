#include "P5.h"

P5_image::P5_image(string filename, int class_numb) {
	cc = class_numb;
	ifstream fin(filename, ios::binary);
	if (!fin.is_open()) {
		cerr << "Can't open file";
		exit(1);
	}
	char c, c1;
	try {
		fin >> c >> c1;
		fin >> width >> height >> depth;
	}
	catch (const exception& e) {
		cerr << "Wrong Header";
		exit(1);
	}
	if (depth > 255 && width < 0 && height < 0 && depth <= 0) {
		cerr << "Wrong Header";
		exit(1);
	}

	if (c != 'P' || c1 != '5') {
		cout << c << " " << c1;

		cerr << "Wrong Header";
		exit(1);
	}

	fin.read(&c, 1);
	try {
		data.assign(height, vector<double>(width));
		newdata.assign(height, vector<double>(width));
	}
	catch (const exception& e) {
		cerr << "troubles with memory";
		exit(1);
	}

	//check header;


	char color_bw;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (fin.eof()) {
				fin.close();
				throw runtime_error("N E pixels");
			}
			fin.read(&color_bw, 1);
			data[i][j] = (double)((unsigned char)color_bw);
		}

	fin.close();
}


void P5_image::write(string filename) {
	ofstream fout(filename, ios::binary);
	if (!fout.is_open()) {
		throw runtime_error("Can't open output file");
	}
	fout << "P5\n" << width << ' ' << height << '\n' << depth << '\n';

	unsigned char press_f;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			press_f = (int)newdata[i][j];
			//cout << press_f << " ";
			fout << press_f;

		}
	}
	fout.flush();
	fout.close();
}


int P5_image::otsuThreshold()
{
	int min = (int)data[0][0];
	int max = (int)data[0][0];

	// ��������� ����������� � ������������ ������� ���� ��������
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; i < width; i++)
		{
			if (data[i][j] < min)
			{
				min = (int)data[i][j];
			}
			if (data[i][j] > max)
			{
				max = (int)data[i][j];
			}
		}
	}

	// ����������� ����� ���������� ����� � ������ ���������� min � max,
	// ������� ��� ������ ��������� ����������� �������� 256 �����
	int histSize = max - min + 1;
	int* hist = new int[histSize];

	// �������� ����������� ������
	for (int t = 0; t < histSize; t++)
		hist[t] = 0;

	// � �������� ������ �����
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; i < width; i++)
		{
			hist[(int)data[i][j] - min]++;
		}
	}


	// ������ ��� ��������������� �����:
	int m = 0; // m - ����� ����� ���� �����, ����������� �� ��������� �� ��������
	int n = 0; // n - ����� ����� ���� �����
	for (int t = 0; t <= max - min; t++)
	{
		m += t * hist[t];
		n += hist[t];
	}

	float maxSigma = -1; // ������������ �������� ������������ ���������
	int threshold = 0; // �����, ��������������� maxSigma

	int alpha1 = 0; // ����� ����� ���� ����� ��� ������ 1
	int beta1 = 0; // ����� ����� ���� ����� ��� ������ 1, ����������� �� ��������� �� ��������

	// ���������� alpha2 �� �����, �.�. ��� ����� m - alpha1
	// ���������� beta2 �� �����, �.�. ��� ����� n - alpha1

	// t ����������� �� ���� ��������� ��������� ������
	for (int t = 0; t < max - min; t++)
	{
		alpha1 += t * hist[t];
		beta1 += hist[t];


		// ������� ����������� ������ 1.
		float w1 = (float)beta1 / n;
		// �������� ����������, ��� w2 ���� �� �����, �.�. ��� ����� 1 - w1

		// a = a1 - a2, ��� a1, a2 - ������� �������������� ��� ������� 1 � 2
		float a = (float)alpha1 / beta1 - (float)(m - alpha1) / (n - beta1);

		// �������, ������� sigma
		float sigma = w1 * (1 - w1) * a * a;

		// ���� sigma ������ ������� ������������, �� ��������� maxSigma � �����
		if (sigma > maxSigma)
		{
			maxSigma = sigma;
			threshold = t;
		}
	}

	// �� �������, ��� ����� ������������ �� min, � �� �� ����
	threshold += min;

	// ���, ����� ��������, ���������� ��� ������ :)
	return threshold;
}
void P5_image::otsu(int class_count)
{

	//Otsu's algorithm variables
	double p1; //first value of the probability in Otsu's algorithm with t = 1


	double* histogram = new double[256];
	double* probability = new double[256];

	double q1; //first value of q qith t = 1
	double q1prev;//previos value of q1
	double q1next;//next value of q1 , aka q1(t+1)
	double mu1; //average of first group, before threshold
	double mu2;//average of second group, after threshold
	double mu1next;//next value of the mean for group 1(mu1(t+1))
	double mu2next;//next value of the mean for group 2(mu2(t+1))
	double mu;//the mean gray level value of the entire image before thresholding
	double betweenvariance = 0.0;//between group variance	
	double maxbetweenvariance = 0.0;//max between group variance
	double sum = 0.0;//sum of all histogram values to calculate the mean grey level value of the imagem values before threshholding
	int pixelvalue = 0;//value of a pixel
	int tmpthresh = 0;
	int* optimizedthresh = new int[class_count];//optimized threshhold, at the end of otsu's algorithm this will be the thresshold with the max between group vairance
	int otp = 0;
	bool changed = false;
	//populate histogram with 0 for all values initially
	for (int k = 0; k <= 255; k++) {
		histogram[k] = 0;
	}
	//populate probability array with 0 for all values initially
	for (int k = 0; k <= 255; k++) {
		probability[k] = 0.0;
	}

	//cycle through entire image and get pixel values and populate the histogram with them
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			pixelvalue = data[i][j];//store pixel value of image at (width,height)
			sum += pixelvalue;//increment the sum of all pixel values , used to calculate the average grey level value of the entire image later one
			histogram[pixelvalue]++;
		}
	}
	//cerr << height * width<<endl;

	for (int k = 0; k <= 255; k++) {
		//	cerr << histogram[k]<<" "<< k <<endl;
	}

	//calculate the probability of each histogram value and store them in the probability array
	for (int k = 0; k <= 255; k++) {
		probability[k] = histogram[k] / (double)(width * height);
		//cerr << histogram[k] << " "<< (width * height) <<endl;
		//cerr << probability[k] << '\n';
	}



	p1 = probability[0];
	q1 = p1;
	mu1 = 0;
	mu2 = 0;
	mu = sum / (width * height);
	int treashold = 0;
	//q -����� ������������ ������ � ��������	
	q1prev = q1;//set previous q1, q1(t), to equal the current q1
	for (int m = 1; m < class_count; m++)
	{
		for (int t = m; t < 255 - class_count - 1; t++)
		{

			q1next = q1prev + probability[t + 1];
			mu1next = (q1prev * mu1 + (t + 1) * (probability[t + 1])) / q1next;
			mu2next = (mu - q1next * mu1next) / (1 - q1next);
			betweenvariance = q1prev * (1 - q1prev) * ((mu1 - mu2) * (mu1 - mu2));
			//cerr << q1next << " " << mu1next << "" << mu2next << endl;
			//cerr << maxbetweenvariance << " " << betweenvariance << endl;
			if (betweenvariance > maxbetweenvariance) {
				maxbetweenvariance = betweenvariance;
				treashold = t;
				//optimizedthresh[otp++] = t;//optimized threshhold
				//cerr << betweenvariance << " " << t << endl;
			}
			q1prev = q1next;
			mu1 = mu1next;
			mu2 = mu2next;

			if (q1next == 0) {
				mu1 = 0;
			}
			
		}
		maxbetweenvariance = 0;
		optimizedthresh[otp++] = (int)treashold;
		//cout << (int)treashold<<endl;
	}
	for (int i = 0; i < class_count; i++)
	{
		for (int j = 0; j < class_count; j++)
		{
			if (optimizedthresh[i] < optimizedthresh[j])
			{
				swap(optimizedthresh[i], optimizedthresh[j]);
			}
		}
	}
	optimizedthresh[class_count] = 255;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			changed = false;
			for (int t = 0; t < class_count+1; t++) {
				if (data[i][j] <= optimizedthresh[t]&&!changed) {
					newdata[i][j] = optimizedthresh[t];
					changed = true;
					//cout << data[i][j] << " " << newdata[i][j]<< " "<< optimizedthresh[t] << endl;
				}
				//newdata[i][j] = data[i][j];
			}
		}
	}
	for (int i = 0; i < class_count; i++)
	{
		cout << optimizedthresh[i]<<endl;
	}
}
