#include "Image.h"
#include <string>
#include <fstream>

bool Image::verbose = true;

Image::Image(const std::string& src, unsigned int width, unsigned height)
	: src_(src), width_(width), height_(height), data_(nullptr)
{
	if (Image::verbose)
		std::cout << "[Image] Create: " << this << std::endl;
	if (src_.length() > 0)
		this->load(src_, width_, height_);
}

Image::~Image(void)
{
	if (Image::verbose)
		std::cout << "[Image] Destroy: " << this << std::endl;
	if (data_)
		delete[] data_;
}

Image::Image(const Image& img)
{
	*this = img;
}

Image&  Image::operator=(const Image& img)
{
	this->width_ = img.get_width();
	this->height_ = img.get_height();
	this->src_ = img.get_src();

	this->data_ = new char[img.size()];
	std::memcpy(this->data_, img.get_data(), img.size());
	return (*this);
}

#include <exception>

void  Image::load(const std::string& img, unsigned int width, unsigned height)
{
	std::ifstream   in(img.c_str(), std::ifstream::in | std::ifstream::binary);

	if (in.fail() || !in.is_open())
		throw std::logic_error("[Image] Can't open :" + img);
	else if (Image::verbose)
		std::cout << "[Image] Open: " << img << std::endl;
	if (width || height)
	{
		width_ = width;
		height_ = height;
	}

	data_ = new char[this->size()];
	in.read(data_, this->size());
	in.close();
}

unsigned int  Image::get_width(void) const { return (width_); }
unsigned int  Image::get_height(void) const { return (height_); }
std::string   Image::get_src() const { return (src_.c_str()); }
char*         Image::get_data() const { return (data_); }
unsigned int  Image::size() const { return (width_ * height_); }
unsigned int  Image::get_pixel(unsigned int x, unsigned int y) const { return (data_[x + y * width_]); }