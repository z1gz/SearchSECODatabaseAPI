/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
� Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "DatabaseHandler.h"
#include "Types.h"

#include <gmock/gmock.h>
#include <string>

using namespace types;

/// <summary>
/// Handles interaction with database.
/// </summary>
class MockStatistics : public Statistics
{
  public:
	MockStatistics()
	{
		registry = std::make_shared<prometheus::Registry>();

		// Create the counter and gauge families.
		requestCounter = &prometheus::BuildCounter()
							  .Name("api_requests_total")
							  .Help("Number of observed requests.")
							  .Register(*registry);

		methodCounter = &prometheus::BuildCounter()
							 .Name("api_methods_total")
							 .Help("Number of recieved methods.")
							 .Register(*registry);

		latestRequest = &prometheus::BuildGauge()
							 .Name("api_request_time_seconds")
							 .Help("The latest time a request has been recieved.")
							 .Register(*registry);
	}
};
