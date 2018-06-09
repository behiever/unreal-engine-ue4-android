
#include "../iTOP/Public/IMSDKComm.h"
 
jobject initListener(JNIEnv *env, long metadataPointer, long resultPointer, int tag) {
	jclass jCls = FAndroidApplication::FindJavaClass("com/tencent/imsdk/cpphelper/IMSDKCppListener");
	jmethodID jInit = env->GetMethodID(jCls, "<init>", "(JJ)V");
	if (jInit == NULL) {
		return NULL;
	}
	jlong jMetadataPointer = (jlong)metadataPointer;
	jlong jResultPointer = (jlong)resultPointer;
	jobject jListener = env->NewObject(jCls, jInit, jMetadataPointer, jResultPointer);
	jmethodID jSetTag = env->GetMethodID(jCls, "setTag", "(I)V");
	env->CallVoidMethod(jListener, jSetTag, (jint)tag);
    env->DeleteLocalRef(jCls);
	return jListener;
}

void IMSDKResult::initialProperties() {
    retCode = 0;
    retMsg = "";
    //new
    imsdkRetCode = -1;
    imsdkRetMsg = "";
    thirdRetCode = -1;
    thirdRetMsg = "";
    retExtraJson = "{}";
}

IMSDKResult::IMSDKResult() {
    initialProperties();
}

IMSDKResult::IMSDKResult(int _retCode) {
    initialProperties();
    retCode = _retCode;
}

IMSDKResult::IMSDKResult(std::string _jsonData) { 
    initialProperties(); 
}

IMSDKResult::IMSDKResult(int _retCode, std::string _retMsg) {
    retCode = _retCode;
    retMsg = _retMsg;
    //new
    imsdkRetCode = -1;
    imsdkRetMsg = "";
    thirdRetCode = -1;
    thirdRetMsg = "";
    retExtraJson = "{}";

}

IMSDKResult::IMSDKResult(int _imsdkRetCode, int _thirdRetCode) {

    retCode = 0;
    retMsg = "deprecated retCode and retMsg";
    //new error code and msg
    imsdkRetCode = _imsdkRetCode;
    imsdkRetMsg = "";
    thirdRetCode = _thirdRetCode;
    thirdRetMsg = "";
    retExtraJson = "{}";
}

IMSDKResult::IMSDKResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg) {
    retCode = 0;
    retMsg = "deprecated retCode and retMsg";
    //new error code and msg
    imsdkRetCode = _imsdkRetCode;
    imsdkRetMsg = _imsdkRetMsg;
    thirdRetCode = _thirdRetCode;
    thirdRetMsg = _thirdRetMsg;
    retExtraJson = "{}";
}

//#pragma mark - IMSDKLoginResult

IMSDKLoginResult::IMSDKLoginResult():IMSDKResult() {
    initialProperties(0, ""); 
}

IMSDKLoginResult::IMSDKLoginResult(int errCode):IMSDKResult(errCode) {
    initialProperties(errCode, "");
}

IMSDKLoginResult::IMSDKLoginResult(std::string _jsonData) : IMSDKResult(_jsonData) {
    initialProperties(0, ""); 
	
} 
 
IMSDKLoginResult::IMSDKLoginResult(int errCode, std::string message):IMSDKResult(errCode,message) {
    initialProperties(errCode, message);

}
/*!
 * 新增构造函数，初始化imsdk、third错误码以及错误信息
 */
IMSDKLoginResult::IMSDKLoginResult(int _imsdkRetCode, int _thirdRetCode):IMSDKResult(_imsdkRetCode,_thirdRetCode){
    initialProperties(0, "");
}

IMSDKLoginResult::IMSDKLoginResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg):IMSDKResult(_imsdkRetCode,_imsdkRetMsg,_thirdRetCode,_thirdRetMsg){

    initialProperties(0, "");
}

void IMSDKLoginResult::initialProperties(int errCode, std::string message) {
    // IMSDKResult
    // guid
    guid_channel_id    = 0;
    guid_game_id       = 0;
    guid               = "";
    guid_open_id       = "";
    guid_token         = "";
    guid_token_expire  = 0;
    guid_user_gender   = 0;
    guid_user_nick     = "";
    guid_user_birthday = "";
    guid_user_portrait = "";

    // channel
    channel            = "";
    channel_userid     = "";
    channel_token      = "";
    // channel_permissions; // 默认初始化
    channel_expire     = 0;
}

//#pragma mark - IMSDKChannelInfo

void IMSDKChannelInfo::initialProperties() {
    channel_id = -1;
    nick = "";
    birthday = "";
    portrait = "";
    gender = -1;
    email = "";
    phone = "";
}

IMSDKChannelInfo::IMSDKChannelInfo() {
    initialProperties();
}

IMSDKChannelInfo::IMSDKChannelInfo(std::string _jsonData) {

    initialProperties();
    
}

//#pragma mark - iIMSDKBindInfo
IMSDKBindInfo::IMSDKBindInfo() {

	login_info = IMSDKLoginResult();
}

IMSDKBindInfo::IMSDKBindInfo(std::string _jsonData) {

    login_info = IMSDKLoginResult(_jsonData); 
}

IMSDKBindInfo::IMSDKBindInfo(int code, std::string msg) {
    login_info = IMSDKLoginResult(code, msg);
    // bind_info 默认初始化为空
}

IMSDKBindInfo::IMSDKBindInfo(int _imsdkCode,int thirdCode){
    login_info = IMSDKLoginResult(_imsdkCode,thirdCode);
}

IMSDKBindInfo::IMSDKBindInfo(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg){
    login_info = IMSDKLoginResult(_imsdkRetCode,_imsdkRetMsg,_thirdRetCode,_thirdRetMsg);
}
 

IMSDKShareRequestInfo::IMSDKShareRequestInfo() {
    type  = IMSDKShareTextSilence;
    title      = "";
    content    = "";
    link       = "";
    thumb_path = "";
    image_path = "";
    extra_json = "";
}

IMSDKShareRequestInfo::IMSDKShareRequestInfo(IMSDKShareType _type, std::string _title, std::string _content, std::string _link, std::string _thumb_path, std::string _image_path, std::string _extra_json) {
    type  = (IMSDKShareType)_type;
    title      = _title;
    content    = _content;
    link       = _link;
    thumb_path = _thumb_path;
    image_path = _image_path;
    extra_json = _extra_json;
}

//#pragma mark - IMSDKFriendInfo
void IMSDKFriendInfo::initialProperties() {
    guid_user_gender = 0;
    guid_open_id = "";
    channel_userid = "";
    guid_user_nick = "";
    guid_user_portrait = "";
}

IMSDKFriendInfo::IMSDKFriendInfo() {
    initialProperties();
}

IMSDKFriendInfo::IMSDKFriendInfo(std::string _jsonData) {
    initialProperties();
    
}

//#pragma mark - IMSDKFriendResult

void IMSDKFriendResult::initialProperties() {
    retCode           = 0;
    guid_channel_id   = 0;
    guid_token_expire = 0;
    guid_user_gender  = 0;
    count             = 0;
}

IMSDKFriendResult::IMSDKFriendResult() {
    initialProperties();
}

IMSDKFriendResult::IMSDKFriendResult(std::string _jsonData) : IMSDKResult(_jsonData) {

    initialProperties();

     
}

IMSDKFriendResult::IMSDKFriendResult(int _retCode, std::string _retMsg) {
    retCode           = _retCode;
    retMsg            = _retMsg;
    guid_channel_id   = 0;
    guid_token_expire = 0;
    guid_user_gender  = 0;
    count             = 0;
}

IMSDKFriendResult::IMSDKFriendResult(int _imsdkRetCode, int _thirdRetCode):IMSDKResult(_imsdkRetCode,_thirdRetCode){
    guid_channel_id   = 0;
    guid_token_expire = 0;
    guid_user_gender  = 0;
    count             = 0;
}

IMSDKFriendResult::IMSDKFriendResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg):IMSDKResult(_imsdkRetCode,_imsdkRetMsg,_thirdRetCode,_thirdRetMsg){
    guid_channel_id   = 0;
    guid_token_expire = 0;
    guid_user_gender  = 0;
    count             = 0;
}

//#pragma mark - IMSDKFriendContent

void IMSDKFriendRequestInfo::initialProperties() {
    type = IMSDKShareTextSilence;
    user = "";
    title = "";
    content = "";
    link = "";
    thumb_path = "";
    image_path = "";
    extra_json = "{}";
}

IMSDKFriendRequestInfo::IMSDKFriendRequestInfo() {
    initialProperties();
}

IMSDKFriendRequestInfo::IMSDKFriendRequestInfo(std::string _jsonData) {
    initialProperties();
    
}

IMSDKFriendRequestInfo::IMSDKFriendRequestInfo(IMSDKShareType _type, std::string _user, std::string _title, std::string _content, std::string _link, std::string _thumb_path, std::string _image_path, std::string _extra_json) {
    type = (IMSDKShareType)_type;
    user = _user;
    title = _title;
    content = _content;
    link = _link;
    thumb_path = _thumb_path;
    image_path = _image_path;
    extra_json = _extra_json;
}

 

IMSDKLocationInfo::IMSDKLocationInfo() {
}

IMSDKLocationInfo::IMSDKLocationInfo(std::string _jsonData) {
    
    
}

//#pragma mark - IMSDKWebViewTicketResult
void IMSDKWebViewTicketResult::initialProperties() {
    retCode = 0;
    retMsg = "";
    imsdkRetCode = -1;
    imsdkRetMsg = "";
    thirdRetCode = -1;
    thirdRetMsg = "";
    retExtraJson = "{}";
    ticket = "";
    domain = "";
}

IMSDKWebViewTicketResult::IMSDKWebViewTicketResult() {
    initialProperties();
}

IMSDKWebViewTicketResult::IMSDKWebViewTicketResult(std::string _jsonData) : IMSDKResult(_jsonData) {
    initialProperties();
    
}

IMSDKWebViewTicketResult::IMSDKWebViewTicketResult(int _retCode, std::string _retMsg) {
    retCode = _retCode;
    retMsg  = _retMsg;
    ticket  = "";
    domain  = "";
}

//#pragma mark - IMSDKHelpFeedbackResult

void IMSDKHelpFeedbackResult::initialProperties() {
    amount = -1;
}

IMSDKHelpFeedbackResult::IMSDKHelpFeedbackResult() : IMSDKResult() {
    initialProperties();
}

IMSDKHelpFeedbackResult::IMSDKHelpFeedbackResult(std::string _jsonData) : IMSDKResult(_jsonData) {
    initialProperties();
    
}

IMSDKHelpFeedbackResult::IMSDKHelpFeedbackResult(int _retCode):IMSDKResult(_retCode),amount(-1){
}

IMSDKHelpFeedbackResult::IMSDKHelpFeedbackResult(int _retCode, std::string _retMsg):IMSDKResult(_retCode,_retMsg),amount(-1){
}

IMSDKHelpFeedbackResult::IMSDKHelpFeedbackResult(int _imsdkRetCode, int _thirdRetCode):IMSDKResult(_imsdkRetCode,_thirdRetCode),amount(-1){
}

IMSDKHelpFeedbackResult::IMSDKHelpFeedbackResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg):IMSDKResult(_imsdkRetCode,_imsdkRetMsg,_thirdRetCode,_thirdRetMsg),amount(-1){
}

//#pragma mark - IMSDKHelpCenterResult

IMSDKHelpCenterResult::IMSDKHelpCenterResult() : IMSDKResult(), state(-1) {

}

IMSDKHelpCenterResult::IMSDKHelpCenterResult(int _retCode) : IMSDKResult(_retCode), state(-1) {
}

IMSDKHelpCenterResult::IMSDKHelpCenterResult(std::string _jsonData) : IMSDKResult(_jsonData) {
    state = -1;
}

IMSDKHelpCenterResult::IMSDKHelpCenterResult(int _retCode, std::string _retMsg):IMSDKResult(_retCode,_retMsg),state(-1){
}

IMSDKHelpCenterResult::IMSDKHelpCenterResult(int _imsdkRetCode, int _thirdRetCode):IMSDKResult(_imsdkRetCode,_thirdRetCode),state(-1){
}

IMSDKHelpCenterResult::IMSDKHelpCenterResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg):IMSDKResult(_imsdkRetCode,_imsdkRetMsg,_thirdRetCode,_thirdRetMsg),state(-1){
}
 

IMSDKNoticeResult::IMSDKNoticeResult():IMSDKResult(){
    initialProperties();
}

IMSDKNoticeResult::IMSDKNoticeResult(std::string _jsonData) : IMSDKResult(_jsonData) {
    initialProperties();
    
}

IMSDKNoticeResult::IMSDKNoticeResult(int _imsdkRetCode, int _thirdRetCode):IMSDKResult(_imsdkRetCode,_thirdRetCode){
    initialProperties();
}

IMSDKNoticeResult::IMSDKNoticeResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg):IMSDKResult(_imsdkRetCode,_imsdkRetMsg,_thirdRetCode,_thirdRetMsg){
    initialProperties();
}
void IMSDKNoticeResult::initialProperties(){
    number = 0;
}
 

IMSDKNoticeInfo::IMSDKNoticeInfo(){
    initialProperties();
}

IMSDKNoticeInfo::IMSDKNoticeInfo(std::string _jsonData) {
    initialProperties();
    
}

void IMSDKNoticeInfo::initialProperties(){
    stateCode = "";
    noticeId = -1;// 公告id
    appId = "";// appid
    openId = "";// 用户open_id
    url = "";// 公告跳转链接
    scene = -1;// 公告展示的场景，管理端后台配置
    startTime = -1;// 公告有效期开始时间
    endTime = -1;// 公告有效期结束时间
    updateTime = -1;// 公告更新时间
    contentType = -1;// 公告内容类型:1:文本公告 2:图片公告 3:网页公告
    category = ""; //公告的分类，登陆前的强制更新公告、登陆后的普通公告等等
    title = "";// 公告标题
    content = "";// 公告内容
    sequenceId = 0; //序列号，表示公告的顺序
    language = "en"; // 公告语种
    publishVersion = "1.0"; // 发布版本号
    contentWebUrl = "";
    extraJson = "";// 扩展
}

 
void IMSDKNoticePicInfo::initialProperties() {
    noticeId = 0;
    screenDir = 0;
    picUrl = "";
    picTitle = "";
    picSize = "";
    mPicHash = "";
    extraJson = "";
}

IMSDKNoticePicInfo::IMSDKNoticePicInfo() {
    initialProperties();
}

IMSDKNoticePicInfo::IMSDKNoticePicInfo(std::string _jsonData) {
    initialProperties();
   
}
 
void IMSDKAuthSNSInfo::initialProperties() {
    channelId = gender = 0;
    openId = userName = pictureUrl = "";
}

IMSDKAuthSNSInfo::IMSDKAuthSNSInfo() {
    initialProperties();
}

IMSDKAuthSNSInfo::IMSDKAuthSNSInfo(std::string _jsonData) {
    initialProperties();
    
}
 
IMSDKAuthResult::IMSDKAuthResult(std::string _jsonData) : IMSDKResult(_jsonData) {
    initialProperties();

    
}

void IMSDKAuthResult::initialProperties() {
    channelId = 0;
    gameId = 0;
    openId = "";
    innerToken = "";
    deviceId = "";
    isFirstLogin = false;
    tokenExpireTime = 0;
}

IMSDKAuthResult::IMSDKAuthResult() : IMSDKResult() {
    initialProperties();
}

IMSDKAuthResult::IMSDKAuthResult(int _imsdkRetCode, int _thirdRetCode):IMSDKResult(_imsdkRetCode,_thirdRetCode) {
    channelId = 0;

    gameId = 0;
    openId = "";
    innerToken = "";
    deviceId = "";
    isFirstLogin = false;
    tokenExpireTime = 0;

}

IMSDKAuthResult::IMSDKAuthResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg):IMSDKResult(_imsdkRetCode,_imsdkRetMsg,_thirdRetCode,_thirdRetMsg) {
    channelId = 0;

    gameId = 0;
    openId = "";
    innerToken = "";
    deviceId = "";
    isFirstLogin = false;
    tokenExpireTime = 0;

//    pictureUrl = "";
//    guid = "";
//    gender = 0;
//    birthday = "";
//    userName = "";

}


 
void IMSDKAuthConnectResult::initialProperties() {
    confirmCode = "";
    openId = "";
    channelId = 0;
    userName = "";
    pictureUrl = "";
    gender = 0;
}

IMSDKAuthConnectResult::IMSDKAuthConnectResult() : IMSDKResult(){
    initialProperties();
}

IMSDKAuthConnectResult::IMSDKAuthConnectResult(std::string _jsonData) : IMSDKResult(_jsonData) {

    initialProperties();

    
}

IMSDKAuthConnectResult::IMSDKAuthConnectResult(int _imsdkRetCode, int _thirdRetCode): IMSDKResult(_imsdkRetCode,_thirdRetCode) {
    confirmCode = "";
    openId = "";
    channelId = 0;
    userName = "";
    pictureUrl = "";
    gender = 0;
}

IMSDKAuthConnectResult::IMSDKAuthConnectResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg) :IMSDKResult(_imsdkRetCode,_imsdkRetMsg,_thirdRetCode,_thirdRetMsg){
    confirmCode = "";
    openId = "";
    channelId = 0;
    userName = "";
    pictureUrl = "";
    gender = 0;
}


//#pragma mark - IMSDKAuthMigrateResult

void IMSDKAuthMigrateResult::initialProperties() {
    migrateCode = "";
    validTime = 0;
    snsInfoVec = std::vector<IMSDKAuthSNSInfo>();
}

IMSDKAuthMigrateResult::IMSDKAuthMigrateResult() : IMSDKResult(){
    initialProperties();
}

IMSDKAuthMigrateResult::IMSDKAuthMigrateResult(std::string _jsonData) : IMSDKResult(_jsonData) {
    initialProperties();
    
}

IMSDKAuthMigrateResult::IMSDKAuthMigrateResult(int _imsdkRetCode, int _thirdRetCode): IMSDKResult(_imsdkRetCode,_thirdRetCode) {
    migrateCode = "";
    validTime = 0;
    snsInfoVec = std::vector<IMSDKAuthSNSInfo>();
//    openId = "";
//    channelId = "";
//    userName = "";
//    pictureUrl = "";
//    gender = 0;
}

IMSDKAuthMigrateResult::IMSDKAuthMigrateResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg) :IMSDKResult(_imsdkRetCode,_imsdkRetMsg,_thirdRetCode,_thirdRetMsg){
    migrateCode = "";
    validTime = 0;
    snsInfoVec = std::vector<IMSDKAuthSNSInfo>();
//    openId = "";
//    channelId = "";
//    userName = "";
//    pictureUrl = "";
//    gender = 0;
}
 
IMSDKLocalNotification::IMSDKLocalNotification() {
    fireTime = 0;
    repeatTpye = 0;
    content = "";
    badge = -1;
    alertAction = "";
    userInfo = std::map<std::string, std::string>();
    type = 0;
    actionType = 0;
    isRinging = false;
    isVibrate = false;
    light = 0;
    builderId = 0;
    styleId = 0;
}

//
////#pragma mark - IMSDKAccount
IMSDKAccount::IMSDKAccount() {
    account = "";
    accountType = 0;
    uid = "";
    token = "";
    extraJson = "{}";
}

IMSDKAccount::IMSDKAccount(std::string _account, int _accountType) {
    account = _account;
    accountType = _accountType;
    uid = "";
    token = "";
    extraJson = "{}";
}

IMSDKAccount::IMSDKAccount(std::string _account, int _accountType, std::string _uid, std::string _token) {
    account = _account;
    accountType = _accountType;
    uid = _uid;
    token = _token;
    extraJson = "{}";
}

//#pragma mark - IMSDKAccountVerifyCodeInfo
IMSDKAccountVerifyCodeInfo::IMSDKAccountVerifyCodeInfo() {
    account = "";
    accountType = 0;
    areaCode = "";
    verifyCode = "";
    timeStamp = 0;
    extraJson = "{}";
}

IMSDKAccountVerifyCodeInfo::IMSDKAccountVerifyCodeInfo(std::string _verifyCode) {
    account = "";
    accountType = 0;
    areaCode = "";
    verifyCode = _verifyCode;
    timeStamp = 0;
    extraJson = "{}";
}

IMSDKAccountVerifyCodeInfo::IMSDKAccountVerifyCodeInfo(std::string _account, int _accountType, std::string _areaCode, std::string _verifyCode) {
    account = _account;
    accountType = _accountType;
    areaCode = _areaCode;
    verifyCode = _verifyCode;
    timeStamp = 0;
    extraJson = "{}";
}

//#pragma mark - IMWebViewStatusResult 
IMWebViewStatusResult::IMWebViewStatusResult() {
    stateCode = 0;
}

IMWebViewStatusResult::IMWebViewStatusResult(std::string _jsonData) : IMSDKResult(_jsonData) {
    stateCode = 0;
    
}


