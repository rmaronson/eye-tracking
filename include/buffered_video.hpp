#ifndef BUFFERED_VIDEO_HPP_
#define BUFFERED_VIDEO_HPP_

#include <cstddef>
#include <opencv2/opencv.hpp>

constexpr int BUF_LEN = 30;


struct Frame {
	typedef std::size_t IdType;

	Frame() : frame(), id() {};
	Frame(Frame const & other) : frame(other.frame.clone()), id(other.id) {}
	Frame(Frame && other) : frame(std::move(other.frame)), id(other.id) {}
	cv::Mat frame;
	IdType id;
};

struct BufferedVideo {
	BufferedVideo(char const * const filename);

	Frame const & cur();
	Frame const & next();
	Frame const & prev();

	double get_property(int val) const;

	std::string const & get_filename() const;

private:

	bool load_next();

	int buf_len;
	int last_id;
	cv::VideoCapture video;
	typedef std::list<Frame> ListType;
	ListType frame_buffer;
	typedef ListType::iterator IteratorType;
	IteratorType current_frame;
	std::string filename;
};

#endif

