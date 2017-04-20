//
//  SPGoogleGeoCoder.h
//  SampleProject
//
//  Created by <#Project Developer#> on 09/12/2015.
//  Copyright © 2015 <#Project Developer#>. All rights reserved.
//

#import "MOGoogleGeocodeList.h"

#import "AFNetworking.h"
#import "AFURLSessionManager.h"
#import "AFURLResponseSerialization.h"
#import "AFURLRequestSerialization.h"
#import "AFSecurityPolicy.h"
#import "AFNetworkReachabilityManager.h"

#import "GoogleMapsHelper.h"

// https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=-33.8670522,151.1957362&radius=500&type=restaurant&name=cruise&key=AIzaSyBFLfst49iEEaYjiP3YIMMDpmH3a3gU8yc



///* --- This is the exception return codes --- */
//static int const kJSONResponseIsOK = -12345678;
//static int const kUnknownErrorCode = 0;
///* ------------------------------------------ */

typedef void(^SPGoogleDirectionsVoidBlock)();
typedef void(^SPGoogleDirectionsPlaceMarksBlock)(MKPolyline *polyLine, NSString *distance, NSString *duration, NSString *startAddress, NSString *endAddress, NSMutableArray *polyLineSetArray, NSMutableArray *directionsSetArray, NSMutableArray *distanceSetArray);
typedef void (^ SPGoogleGeoCoderCompletionBlock) (MOGoogleGeocodeList *googleGeoCodeList, SPGoogleGeoCoderResponse responseCode, NSString *message);
typedef void (^ SPGoogleAutoCompletionBlock) (MOGoogleAutoCompleteList *googleAutocompleteList, SPGoogleGeoCoderResponse responseCode, NSString *message);

@interface AFGoogleMapsHelper : AFHTTPSessionManager
/**
 *  Google API key. Not required, but result filtering on reverse geocoding is only available when set.
 */
@property (nonatomic, strong) NSString *APIKey;
/**
 *  Operation Queue for requesting a call. Currently not being used.
 */
@property (nonatomic, strong) NSOperationQueue *requestQueue;

/**
 *  sharedGoogleMapHelper
 *
 *  @return a singleton
 */
+ (instancetype)sharedAFGoogleMapsHelper;

/**
 *@description Asynchroniously queries the Google Geocoder API with the data provided.
 *@param query A free search query string
 *@param components A dictionary containing filters.
 *@see https://developers.google.com/maps/documentation/geocoding/#ComponentFiltering for possible filter values.
 *@param completionHandler Upon completion or failure this will be invoked. Passes an array of IRTSGooglePlacemark objects (or empty if no results). If an error occured, the "error" object will be != nil
 **/
//https://maps.googleapis.com/maps/api/geocode/json?address=1600+Amphitheatre+Parkway,+Mountain+View,+CA&key=AIzaSyBIZaLWmbSWXn7LDU-Na54rxGYtn61uiW0
- (void)geocodeAddressString:(NSString *)query components:(NSDictionary *)components completionHandler:(SPGoogleGeoCoderCompletionBlock)completion;

/**
 *@description Asynchroniously queries the Google Geocoder API with the data provided.
 *@see https://developers.google.com/maps/documentation/geocoding/#Types and https://developers.google.com/maps/documentation/geocoding/#ReverseGeocoding for possible filter values.
 *@param coordinate Coordinate to look up
 *@param resultTypes A dictionary containing result type filters. NOTE: Ignored if APIKey == nil.
 *@param key — Your application's API key, obtained from the Google Developers Console. This key identifies your application for purposes of quota management.
 *@param language — The language in which to return results. See the list of supported domain languages. Note that we often update supported languages so this list may not be exhaustive. If language is not supplied, the geocoder will attempt to use the native language of the domain from which the request is sent wherever possible.
 *@param result_type — One or more address types, separated by a pipe (|). Examples of address types: country, street_address, postal_code. For a full list of allowable values, see the address types on this page. Specifying a type will restrict the results to this type. If multiple types are specified, the API will return all addresses that match any of the types. Note: This parameter is available only for requests that include an API key or a client ID.
 *@param location_type — One or more location types, separated by a pipe (|). Specifying a type will restrict the results to this type. If multiple types are specified, the API will return all addresses that match any of the types. Note: This parameter is available only for requests that include an API key or a client ID. The following values are supported:
 "ROOFTOP" restricts the results to addresses for which we have location information accurate down to street address precision.
 "RANGE_INTERPOLATED" restricts the results to those that reflect an approximation (usually on a road) interpolated between two precise points (such as intersections). An interpolated range generally indicates that rooftop geocodes are unavailable for a street address.
 "GEOMETRIC_CENTER" restricts the results to geometric centers of a location such as a polyline (for example, a street) or polygon (region).
 "APPROXIMATE" restricts the results to those that are characterized as approximate.
 
 If both result_type and location_type restrictions are present then the API will return only those results that matches both the result_type and the location_type restrictions.
 
 *@param locationTypes A dictionary containing location type filters. NOTE: Ignored if APIKey == nil.
 *@param completionHandler Upon completion or failure this will be invoked. Passes an array of NOGooglePlacemark objects (or empty if no results). If an error occured, the "error" object will be != nil
 **/
- (void)reverseGeocodeCoordinate:(CLLocationCoordinate2D)coordinate resultTypes:(NSArray *)resultTypes locationTypes:(NSArray *)locationTypes completionHandler:(SPGoogleGeoCoderCompletionBlock)completion;

/**
 *  <#Description#>
 *
 *  @param coordinateSource      <#coordinateSource description#>
 *  @param coordinateDestination <#coordinateDestination description#>
 *  @param drawPoints            <#drawPoints description#>
 *  @param placeMarks            <#placeMarks description#>
 */

//https://maps.googleapis.com/maps/api/directions/json?origin=75+9th+Ave+New+York,+NY&destination=MetLife+Stadium+1+MetLife+Stadium+Dr+East+Rutherford,+NJ+07073&key=AIzaSyC8qVrP393qjTl4SO0bYi49uB_tfJ_htjo
- (void)getDirections:(CLLocationCoordinate2D)coordinateSource andCoordinateDestination:(CLLocationCoordinate2D)coordinateDestination  andDrawPoints:(SPGoogleDirectionsVoidBlock)drawPoints andPlaceMarks:(SPGoogleDirectionsPlaceMarksBlock)placeMarks;

/**
 *  Google autocomplete for places will res
 *
 *  @param keyWord      <#keyWord description#>
 *  @param autocomplete <#autocomplete description#>
 */
// https://maps.googleapis.com/maps/api/place/autocomplete/json?input=Amoeba&types=establishment&location=37.76999,-122.44696&radius=500&key=AIzaSyDxbUjg12elRDjWOifMfxHyHA77pVIeMh4
- (void)getAutoCompleteFromGoogle:(NSString *)keyWord andAutoComplete:(SPGoogleAutoCompletionBlock)autocomplete;


@end
