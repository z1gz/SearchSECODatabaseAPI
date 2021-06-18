/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include "DatabaseHandler.h"
#include "HTTPStatus.h"
#include "JobRequestHandler.h"
#include "DatabaseRequestHandler.h"
#include "RAFTConsensus.h"
#include "DatabaseConnection.h"

#include <boost/shared_ptr.hpp>

class TcpConnection;

/// <summary>
/// The different types of requests which are supported.
/// </summary>
enum eRequestType
{
	eUpload,
	eCheck,
	eCheckUpload,
	eConnect,
	eUploadJob,
	eUploadCrawlData,
	eGetTopJob,
	eExtractProjects,
	eGetAuthorID,
	eGetAuthor,
	eGetMethodByAuthor,
	eGetPrevProjectsRequest,
	eUnknown
};


class RequestHandler
{
public:

	/// <summary>
	/// Makes the RequestHandler ready for later usage.
	/// </summary>
	/// <param name="databaseHandler">
	/// Handler for interactions with the database.
	/// </param>
	virtual void initialize(DatabaseHandler *databaseHandler, DatabaseConnection *databaseConnection, RAFTConsensus* raft, std::string ip = IP, int port = DBPORT);

	/// <summary>
	/// Handles all requests send to the database.
	/// </summary>
	/// <param name="requestType">
	/// Type of the request, a string of exactly 4 characters.
	/// </param>
	/// <param name="request">
	/// The request made by the user, a string containing all
	/// relevant data in a specific order to be able to do the request.
	/// </param>
	/// <returns>
	/// Response towards user after processing the request successfully.
	/// </returns>
	virtual std::string handleRequest(std::string requestType, std::string request, boost::shared_ptr<TcpConnection> connection);
private:

	/// <summary>
	/// Handles unknown requests.
	/// </summary>
	/// <returns>
	/// A message telling the user that their input is not recognised.
	/// </returns>
	std::string handleUnknownRequest();

	/// <summary>
	/// Handles not implemented requests.
	/// </summary>
	/// <returns>
	/// A message telling the user that their input is not implemented yet.
	/// </returns>
	std::string handleNotImplementedRequest();

	/// <summary>
	/// Converts a requestType into an eRequestType.
	/// </summary>
	/// <param name="requestType">
	/// The type of the request, which is a string of exactly 4 characters.
	/// </param>
	/// <returns>
	/// A corresponding eRequestType.
	/// </returns>
	eRequestType getERequestType(std::string requestType);

	DatabaseRequestHandler* dbrh;
	JobRequestHandler* jrh;
};
