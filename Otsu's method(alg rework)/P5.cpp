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



int P5_image::otsu(int t1, int t2)
{
	if (t1>t2)
	{
		swap(t1, t2);
	}
	double p1;
	double* histogram = new double[256];
	double* probability = new double[256];

	double q1;
	double q1prev;
	double q1next;
	double mu1;
	double mu2;
	double mu1next;
	double mu2next;
	double mu;
	double betweenvariance = 0.0, maxbetweenvariance = 0.0, sum = 0.0;
	int pixelvalue = 0;
	int tmpthresh = 0;
	int otp = 0;
	bool changed = false;

	for (int k = 0; k <= 255; k++) {
		histogram[k] = 0;
	}

	for (int k = 0; k <= 255; k++) {
		probability[k] = 0.0;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			pixelvalue = data[i][j];
			sum += pixelvalue;
			histogram[pixelvalue]++;
		}
	}

	for (int k = 0; k <= 255; k++) {
		probability[k] = histogram[k] / (double)(width * height);
	}



	p1 = probability[0];
	q1 = p1;
	mu1 = 1;
	mu2 = 0;
	mu = sum / (width * height);
	q1prev = q1;


		q1next = q1prev + probability[t1 + 1];
		mu1next = (q1prev * mu1 + (t1 + 1) * (probability[t1 + 1])) / q1next;
		mu2next = (mu - q1next * mu1next) / (1 - q1next);
		betweenvariance = q1prev * (1 - q1prev) * ((mu1 - mu2) * (mu1 - mu2));
		q1prev = q1next;
		mu1 = mu1next;
		mu2 = mu2next;
		q1next = q1prev + probability[t2 + 1];
		mu1next = (q1prev * mu1 + (t2 + 1) * (probability[t2 + 1])) / q1next;
		mu2next = (mu - q1next * mu1next) / (1 - q1next);
		betweenvariance += q1prev * (1 - q1prev) * ((mu1 - mu2) * (mu1 - mu2));
		delete histogram;
		delete probability;


	return betweenvariance;
}

void  P5_image::multytresholding(int class_count) {
	bool changed;
	int p1 = 0, p2 = 0;
	int maxbetvar = 0;
	int betvar = 0;
	int* optimizedthresh = new int[class_count - 1];
	int* colors = new int[class_count];
	for (int i = 0; i < class_count - 1; i++)
	{
		optimizedthresh[i] = 0;
	}
	for (size_t i = 1; i < 254; i++)
	{
		for (int j = i + 1; j < 255; j++)
		{
			if (i != j) {
				betvar = otsu(i, j);
				if (betvar > maxbetvar)
				{
					maxbetvar = betvar;
					p1 = i;
					p2 = j;
				}
			}
		}
	}
	cerr << p1 << " " << p2;

	if (p1>p2)
	{
		swap(p1, p2);
	}

	optimizedthresh[0] = p1;
	optimizedthresh[1] = p2;
	optimizedthresh[2] = 255;

	

	for (int i = 1; i < class_count - 1; i++)
	{
		colors[i] = (int)(255 * i / (class_count - 1));
		//cerr << colors[i]<<endl;
	}
	colors[0] = 0;
	colors[class_count - 1] = 255;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			if (data[i][j] < p1)
			{
				newdata[i][j] = colors[0];
			}
			else if (p2 >= data[i][j]&& data[i][j] >= p1)
			{
				newdata[i][j] = colors[1];
			}
			else if (p2 < data[i][j])
			{
				newdata[i][j] = colors[2];
			}
			//cerr << data[i][j] << " " << newdata[i][j] << endl;
		}
	}
	delete optimizedthresh;
	delete colors;
}

void P5_image::otsu2(int class_count) {
	double p1;
	double* histogram = new double[256];
	double* probability = new double[256];

	double q1;
	double q1prev;
	double q1next;
	double mu1;
	double mu2;
	double mu1next;
	double mu2next;
	double mu;
	double betweenvariance = 0.0, maxbetweenvariance = 0.0, sum = 0.0;
	int pixelvalue = 0;
	int tmpthresh = 0;
	int otp = 0;
	bool changed = false;

	for (int k = 0; k <= 255; k++) {
		histogram[k] = 0;
	}

	for (int k = 0; k <= 255; k++) {
		probability[k] = 0.0;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			pixelvalue = data[i][j];
			sum += pixelvalue;
			histogram[pixelvalue]++;
		}
	}

	for (int k = 0; k <= 255; k++) {
		probability[k] = histogram[k] / (double)(width * height);
	}



	p1 = probability[0];
	q1 = p1;
	mu1 = 1;
	mu2 = 0;
	mu = sum / (width * height);
	q1prev = q1;

	for (int i = 1; i < 254; i++)
	{
		q1next = q1prev + probability[i + 1];
		mu1next = (q1prev * mu1 + (i + 1) * (probability[i + 1])) / q1next;
		mu2next = (mu - q1next * mu1next) / (1 - q1next);
		betweenvariance = q1prev * (1 - q1prev) * ((mu1 - mu2) * (mu1 - mu2));
		
		q1prev = q1next;
		mu1 = mu1next;
		mu2 = mu2next;
		if (betweenvariance>maxbetweenvariance)
		{
			maxbetweenvariance = betweenvariance;
			otp = i;
		}
		if (q1next == 0) {
			mu1 = 0;
		}
	}

	//	cerr << otp;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			if (data[i][j] < otp)
			{
				newdata[i][j] = 0;
			}
			else
			{
				newdata[i][j] = 255;
			}
			//cerr << data[i][j] << " " << newdata[i][j] << endl;
		}
	}

	delete histogram;
	delete probability;
}