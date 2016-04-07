/**
	@author Peter Sands
	Email: w1541805@apps.losrios.edu

	@file Report.h
	@brief class for generating reports

*/

#ifndef PSANDS_CISP430_REPORT_H
#define PSANDS_CISP430_REPORT_H

#include <string>

/**
	@brief namespace for assignment 2
*/
namespace psands_cisp430_a2
{
	/// For generating reports for assignments
	class Report
	{
	private:
		std::string _reportHeader; ///< contains the reports header
		std::string _reportTitle; ///< contains the reports title
		std::string _reportBody; ///< contains the reports body

	public:
		/**
			default constructor initializes the report to blank state
		*/
		Report();
		/**
			parameterized constructor initializes report with a header and title
		*/
		Report(std::string reportHeader, std::string reportTitle);
		/**
			copy constructor copies the contents of one report into this report
		*/
		Report(const Report & report);

		/**
			sets the report header to the value of the report header parameter
			@param reportHeader the value to set this report's header to
		*/
		void setReportHeader(std::string reportHeader);
		/**
			sets the report title to the value of the report title parameter
			@param reportTitle the value to set this report's title to
		*/
		void setReportTitle(std::string reportTitle);
		/**
			adds content to the body of the report
			@param content the content to add to the body of the report
		*/
		void addContent(std::string content);

		/**
			returns a string containing the full report
		*/
		std::string generateReport() const;

		/**
		outputs the content of the report to a file
		@param filename the file to output the report to
		*/
		void saveReport(std::string filename) const;
	};	
}

#endif  // PSANDS_CISP430_REPORT_H