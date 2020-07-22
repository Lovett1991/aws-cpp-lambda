#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/ScanRequest.h>
#include <aws/lambda-runtime/runtime.h>
#include <iostream>

using namespace aws::lambda_runtime;

invocation_response my_handler(invocation_request const& request)
{

   Aws::Client::ClientConfiguration clientConfig;
   clientConfig.region = std::getenv("AWS_REGION");
   Aws::DynamoDB::DynamoDBClient client(clientConfig);

   const Aws::DynamoDB::Model::ScanRequest scanRequest = Aws::DynamoDB::Model::ScanRequest().WithTableName("service-catalog.services");
   std::cout << "about to scan" << std::endl;
   const Aws::DynamoDB::Model::ScanOutcome &scanResult = client.Scan(scanRequest); // Time out here
   std::cout << "scan complete" << std::endl;

   return invocation_response::success(scanResult.IsSuccess() ? "true" : "false", "application/json");
}

int main()
{
   Aws::SDKOptions options;
   Aws::InitAPI(options);

   run_handler(my_handler);

   Aws::ShutdownAPI(options);
   return 0;
}