//
//  HTTPServer.h
//  TextTransfer
//
//  Created by Matt Gallagher on 2009/07/13.
//  Copyright 2009 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file, free of charge, in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

typedef enum
{
	SERVER_STATE_IDLE,
	SERVER_STATE_STARTING,
	SERVER_STATE_RUNNING,
	SERVER_STATE_STOPPING
} HTTPProxyServerState;

static const int HTTP_SERVER_PORT = 8080;

@class HTTPResponseHandler;

@interface HTTPProxyServer : NSObject <NSNetServiceDelegate>
{
	NSError *lastError;
	NSFileHandle *listeningHandle;
	CFSocketRef socket;
	HTTPProxyServerState state;
	NSMutableDictionary *incomingRequests;
	NSMutableSet *responseHandlers;
    NSNetService *netService;
}

@property (nonatomic, readonly, retain) NSError *lastError;
@property (readonly, assign) HTTPProxyServerState state;
@property (nonatomic, readonly) UInt32 httpServerPort;
@property (nonatomic) NSInteger socksProxyPort;

+ (HTTPProxyServer *)sharedHTTPServer;
+ (HTTPProxyServer *)sharedHTTPServerWithSocksProxyPort: (NSInteger) socksProxyPort;

- (void)start;
- (void)stop;

- (void)closeHandler:(HTTPResponseHandler *)aHandler;

@end

extern NSString * const HTTPServerNotificationStateChanged;
