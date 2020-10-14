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



void P5_image::otsu2(int class_count)
{
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
	int* optimizedthresh = new int[class_count + 1];
	int* colors = new int[class_count];
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
	//cerr << height * width<<endl;

	for (int k = 0; k <= 255; k++) {
		//	cerr << histogram[k]<<" "<< k <<endl;
	}


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
	q1prev = q1;//set previous q1, q1(t), to equal the current q1
	for (int m = 1; m < class_count; m++)
	{
		for (int k = 255 - class_count - 1; k > m; k--)
		{
			q1prev = probability[m];

			for (int t = m; t < k; t++)
			{

				q1next = q1prev + probability[t + 1];
				mu1next = (q1prev * mu1 + (t + 1) * (probability[t + 1])) / q1next;
				mu2next = (mu - q1next * mu1next) / (1 - q1next);
				//betweenvariance = q1next * ((mu1 - mu2) * (mu1 - mu2));
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

	/*auto change_bitness = [&class_count, this](double pixel_color) {
		return (int)255*round(pixel_color * ((1 <<(class_count-1)) - 1) / 255) / ((1 << (class_count-1)) - 1);
	};

	//cerr << change_bitness(127) << endl;
	for (int i = 0; i < class_count+1; i++)
	{
		colors[i] = change_bitness( 255 * i / class_count);
		cerr << colors[i] << endl;
	}*/
	colors[0] = 0;
	colors[class_count - 1] = 255;
	for (int i = 1; i < class_count - 1; i++)
	{
		colors[i] = (int)(255 * i / (class_count - 1));

	}
	optimizedthresh[class_count] = 255;
	/*for (int i = 0; i <class_count; i++)
	{
		cerr << colors[i]<<endl;
	}*/
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			changed = false;
			for (int t = 1; t < class_count + 1; t++) {
				if (data[i][j] <= optimizedthresh[t] && data[i][j] >= optimizedthresh[t - 1] && !changed) {
					//newdata[i][j] = change_bitness(newdata[i][j]);
					newdata[i][j] = colors[t - 1];
					changed = true;
					//cout << data[i][j] << " " << newdata[i][j]<< " "<< optimizedthresh[t] << endl;
				}
				//newdata[i][j] = data[i][j];
			}
		}
	}
	for (int i = 1; i < class_count; i++)
	{
		cout << optimizedthresh[i] << endl;
	}
	delete probability;
	delete histogram;
	delete optimizedthresh;
	delete colors;
}

void P5_image::otsu(int class_count)
{
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
	int* optimizedthresh = new int[class_count + 1];
	int* colors = new int[class_count];
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
	//cerr << height * width<<endl;

	for (int k = 0; k <= 255; k++) {
		//	cerr << histogram[k]<<" "<< k <<endl;
	}


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
	q1prev = q1;//set previous q1, q1(t), to equal the current q1
	for (int m = 1; m < class_count; m++)
	{
		for (int k = 255 ; k > m; k--)
		{
			//q1prev = probability[m];

			for (int t = m; t < k; t++)
			{

				q1next = q1prev + probability[t + 1];
				mu1next = (q1prev * mu1 + (t + 1) * (probability[t + 1])) / q1next;
				mu2next = (mu - q1next * mu1next) / (1 - q1next);
				betweenvariance = q1next * ((mu1 - mu2) * (mu1 - mu2));
				//betweenvariance = q1prev * (1 - q1prev) * ((mu1 - mu2) * (mu1 - mu2));
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

	/*auto change_bitness = [&class_count, this](double pixel_color) {
		return (int)255*round(pixel_color * ((1 <<(class_count-1)) - 1) / 255) / ((1 << (class_count-1)) - 1);
	};

	//cerr << change_bitness(127) << endl;
	for (int i = 0; i < class_count+1; i++)
	{
		colors[i] = change_bitness( 255 * i / class_count);
		cerr << colors[i] << endl;
	}*/
	colors[0] = 0;
	colors[class_count - 1] = 255;
	for (int i = 1; i < class_count - 1; i++)
	{
		colors[i] = (int)(255 * i / (class_count - 1));

	}
	optimizedthresh[class_count] = 255;
	/*for (int i = 0; i <class_count; i++)
	{
		cerr << colors[i]<<endl;
	}*/
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			changed = false;
			for (int t = 1; t < class_count + 1; t++) {
				if (data[i][j] <= optimizedthresh[t] && data[i][j] >= optimizedthresh[t - 1] && !changed) {
					//newdata[i][j] = change_bitness(newdata[i][j]);
					newdata[i][j] = colors[t - 1];
					changed = true;
					//cout << data[i][j] << " " << newdata[i][j]<< " "<< optimizedthresh[t] << endl;
				}
				//newdata[i][j] = data[i][j];
			}
		}
	}
	for (int i = 1; i < class_count; i++)
	{
		cout << optimizedthresh[i] << endl;
	}
	delete probability;
	delete histogram;
	delete optimizedthresh;
	delete colors;
}