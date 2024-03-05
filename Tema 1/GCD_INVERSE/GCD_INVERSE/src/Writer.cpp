#include "pch.h"
#include "Writer.h"


Writer::Writer(std::string_view filename)
{
	std::string dir = std::string("result/") + filename.data();
	if (!std::filesystem::exists(dir))
	{
		std::filesystem::create_directory(dir);
	}
	m_OutputStream = std::make_shared<std::ofstream>((dir + "/" + filename.data() + ".tex").c_str());

	*m_OutputStream << R"(
\documentclass[a4paper, 14pt]{scrartcl}

\usepackage{amsmath, amssymb}
\usepackage{paracol}
\DeclareMathOperator{\cmmdc}{cmmdc}
\DeclareMathOperator{\arctg}{arctg}
\DeclareMathOperator{\tg}{tg}
\DeclareMathOperator{\ctg}{ctg}
\DeclareMathOperator{\arcctg}{arcctg}
\DeclareMathOperator{\arccsc}{arccsc}
\DeclareMathOperator{\arcsech}{arcsech}
\DeclareMathOperator{\arccoth}{arccoth}

\begin{document}
)";
}

Writer::~Writer()
{
	Close();
}

void Writer::Close()
{
	*m_OutputStream << R"(
\end{document}
)";

	m_OutputStream->close();
}


