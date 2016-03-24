#include <fstream>
#include "Report.h"

using namespace psands_cisp430_a2;

Report::Report()
{
}

/**
\code{.unparsed}
	set this report header to the parameter reportHeader
	set this report title to the parameter reportTitle
\endcode
*/
Report::Report(std::string reportHeader, std::string reportTitle)
{
	this->setReportHeader(reportHeader);
	this->setReportTitle(reportTitle);
}

/**
\code{.unparsed}
	may call parameterized constructor to initialize header and title
	then set this report body to the copy report body
\endcode
*/
Report::Report(const Report & report) : Report(report._reportHeader, report._reportTitle)
{
	this->_reportBody = report._reportBody;
}

/**
\code{.unparsed}
	set this report header to parameter reportHeader
\endcode
*/
void Report::setReportHeader(std::string reportHeader)
{
	this->_reportHeader = reportHeader;
}

/**
\code{.unparsed}
	set this reportTitle to parameter reportTitle
\endcode
*/
void Report::setReportTitle(std::string reportTitle)
{
	this->_reportTitle = reportTitle;
}

/**
\code{.unparsed}
	append parameter content to this report's body
\endcode
*/
void Report::addContent(std::string content)
{
	this->_reportBody += content;
}

/**
\code{.unparsed}
	return a concatenation of this report's header, title and body
\endcode
*/
std::string Report::generateReport() const
{
	return this->_reportHeader + this->_reportTitle + this->_reportBody;
}

/**
\code{.unparsed}
	store the generated report to disk using parameter filename
		open file
		output generated report
		close file
\endcode
*/
void Report::saveReport(char * filename) const
{
	std::ofstream output;
	output.open(filename);
	output << this->generateReport();
	output.close();
}
