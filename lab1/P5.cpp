#include "P5.h"

P5_image::P5_image(string filename) {
	ifstream fin(filename, ios::binary);
	char c;
	fin >> c >> c;
	fin >> width >> height >> depth;
	fin.read(&c, 1);
	data.assign(height, vector<unsigned char>(width));

	char color_bw;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (fin.eof()) {
				fin.close();
				throw runtime_error("N E pixels");
			}
			fin.read(&color_bw, 1);
			data[i][j] = color_bw;
		}
	fin.close();
}

void P5_image::write(string filename) {
	ofstream fout(filename, ios::binary);
	if (!fout.is_open()) {
		throw runtime_error("Can't open output file");
	}
	fout << "P5\n" << width << ' ' << height << '\n' << depth << '\n';
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fout << (data[i][j]);
		}
	}
	fout.flush();
	fout.close();
}

void P5_image::inversion() {
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = depth - data[i][j];
}

void P5_image::rotate_right() {
	vector<vector<unsigned char>> new_image(width, vector<unsigned char>(height));
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			new_image[j][height - i - 1] = data[i][j];
	data = new_image;
	swap(height, width);
}

void P5_image::rotate_left() {
	vector<vector<unsigned char>> new_image(width, vector<unsigned char>(height));
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			new_image[width - j - 1][i] = data[i][j];
	data = new_image;
	swap(height, width);
}

void P5_image::horizontal_reflection() {
	for (int i = 0; i < height; i++)
		reverse(data[i].begin(), data[i].end());
}

void P5_image::vertical_reflection() {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height / 2; j++)
			swap(data[j][i], data[height - j - 1][i]);
}
