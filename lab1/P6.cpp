#include "P6.h"

P6_image::P6_image(string filename) {
	ifstream fin(filename, ios::binary);
	char c;
	fin >> c >> c;
	fin >> width >> height >> depth;
	fin.read(&c, 1);
	data.assign(height, vector<color>(width));

	char color_rgb[3];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (fin.eof()) {
				fin.close();
				throw runtime_error("N E pixels");
			}
			fin.read(color_rgb, 3);
			data[i][j] = { color_rgb[0], color_rgb[1], color_rgb[2] };
		}
	fin.close();
}

void P6_image::write(string filename) {
	ofstream fout(filename, ios::binary);
	if (!fout.is_open()) {
		throw runtime_error("Can't open output file");
	}
	fout << "P6\n" << width << ' ' << height << '\n' << depth << '\n';
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fout << char(std::get<0>(data[i][j])) << char(std::get<1>(data[i][j])) << char(std::get<2>(data[i][j]));
		}
	}
	fout.flush();
	fout.close();
}

void P6_image::inversion() {
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = { depth - std::get<0>(data[i][j]), depth - std::get<1>(data[i][j]), depth - std::get<2>(data[i][j]) };
}

void P6_image::rotate_right() {
	vector<vector<color>> new_image(width, vector<color>(height));
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			new_image[j][height - i - 1] = data[i][j];
	data = new_image;
	swap(height, width);
}

void P6_image::rotate_left() {
	vector<vector<color>> new_image(width, vector<color>(height));
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			new_image[width - j - 1][i] = data[i][j];
	data = new_image;
	swap(height, width);
}

void P6_image::horizontal_reflection() {
	for (int i = 0; i < height; i++)
		reverse(data[i].begin(), data[i].end());
}

void P6_image::vertical_reflection() {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height / 2; j++)
			swap(data[j][i], data[height - j - 1][i]);
}
