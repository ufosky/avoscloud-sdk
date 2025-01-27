//
//  AVGroup.h
//  AVOS
//
//  Created by Qihe Bian on 7/22/14.
//
//

#import <Foundation/Foundation.h>
#import "AVConstants.h"
#import "AVMessage.h"

@class AVSession;
@class AVGroup;
@protocol AVGroupDelegate;

typedef enum : NSUInteger {
    AVGroupEventSelfJoined = 1,
    AVGroupEventSelfLeft,
    AVGroupEventSelfRejected,
    AVGroupEventMemberJoined,
    AVGroupEventMemberLeft,
    AVGroupEventMemberInvited,
    AVGroupEventMemberKicked
} AVGroupEvent;

typedef void (^AVGroupResultBlock)(AVGroup *group, NSError *error);
@interface AVGroup : NSObject

@property (nonatomic, weak) id <AVGroupDelegate> delegate;
@property (nonatomic, readonly) NSString *groupId;
@property (nonatomic, weak) AVSession *session;

/*!
 *  异步创建一个新group并加入此group
 *  @param session group依赖的服务器会话
 *  @param groupDelegate group使用的delegate
 *  @param callback group创建成功或失败的回调
 */
+ (void)createGroupWithSession:(AVSession *)session
                 groupDelegate:(id<AVGroupDelegate>)groupDelegate
                      callback:(AVGroupResultBlock)callback;

/*!
 *  根据groupId获取一个AVGroup对象
 *  @param groupId 已经存在的groupId，不能为nil
 *  @param session group依赖的服务器会话
 *  @return 返回group对象
 */
+ (AVGroup *)getGroupWithGroupId:(NSString *)groupId session:(AVSession *)session;

/*!
 *  加入group
 */
- (void)join;

/*!
 *  向group发送消息
 *  @param message 消息对象
 */
- (void)sendMessage:(AVMessage *)message;

/*!
 *  向group发送消息
 *  @param message 消息对象
 *  @param transient 设置为 YES, 当且仅当某个 peer 在线才会收到该条消息，且该条消息既不会存为离线消息，也不会通过消息推送系统发出去.
 *         如果设置为 NO, 则该条消息会设法通过各种途径发到 peer 客户端，比如即时通信、推送、离线消息等。
 */
- (void)sendMessage:(AVMessage *)message transient:(BOOL)transient;

- (void)sendMessage:(NSString *)message isTransient:(BOOL)transient AVDeprecated("2.6.4");

/*!
 *  将指定peerIds踢出group
 *  @param peerIds 需要踢出group的peerId列表
 *  @return 无异常返回YES，否则返回NO
 */
- (void)kickPeerIds:(NSArray *)peerIds;

- (BOOL)kick:(NSArray *)peerIds AVDeprecated("2.6.4");

/*!
 *  邀请peerIds加入group
 *  @param peerIds 需要邀请的peerId列表
 *  @return 无异常返回YES，否则返回NO
 */
- (void)invitePeerIds:(NSArray *)peerIds;

- (BOOL)invite:(NSArray *)peerIds  AVDeprecated("2.6.4");

/*!
 *  退出group
 *  @return 无异常返回YES，否则返回NO
 */
- (void)quit;

@end

@protocol AVGroupDelegate <NSObject>
@optional
- (void)group:(AVGroup *)group didReceiveMessage:(AVMessage *)message;
- (void)group:(AVGroup *)group didReceiveEvent:(AVGroupEvent)event peerIds:(NSArray *)peerIds;
- (void)group:(AVGroup *)group messageSendFinished:(AVMessage *)message;
- (void)group:(AVGroup *)group messageSendFailed:(AVMessage *)message error:(NSError *)error;


- (void)session:(AVSession *)session group:(AVGroup *)group didReceiveGroupMessage:(NSString *)message fromPeerId:(NSString *)peerId  AVDeprecated("2.6.4");
- (void)session:(AVSession *)session group:(AVGroup *)group didReceiveGroupEvent:(AVGroupEvent)event memberIds:(NSArray *)memberIds  AVDeprecated("2.6.4");
- (void)session:(AVSession *)session group:(AVGroup *)group messageSent:(NSString *)message success:(BOOL)success  AVDeprecated("2.6.4");

@end
