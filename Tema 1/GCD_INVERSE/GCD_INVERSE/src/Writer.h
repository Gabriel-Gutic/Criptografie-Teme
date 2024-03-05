#pragma once


class Writer
{
public:
	Writer(std::string_view filename);
	Writer(const Writer&) = delete;
	~Writer();

	void Close();
	
	template <typename T>
	friend Writer& operator<<(Writer& writer, const T& text);
private:
	std::shared_ptr<std::ofstream> m_OutputStream;
};

template<typename T>
inline Writer& operator<<(Writer& writer, const T& text)
{
	*(writer.m_OutputStream) << text;
	return writer;
}
