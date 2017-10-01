#pragma once
#include<libtransistor/ipc.h>

using ServiceName = uint8_t *; // uint8_t[8]

class SmService;
namespace Pm {
	class Bm;
	class Shell;
}
namespace nn {
	using ApplicationId = uint64_t;
	using TimeSpan = uint64_t;
	using TimeSpanType = uint64_t;
}
namespace nn::account {
	using CallbackUri = uint8_t;
	using NetworkServiceAccountId = uint64_t;
	using Nickname = uint8_t *; // uint8_t[0x21]
	using NintendoAccountAuthorizationRequestParameters = uint8_t;
	using NintendoAccountId = uint64_t;
	using ProfileDigest = uint128_t;
	using RequestUrl = uint8_t;
	using SystemProgramIdentification = uint8_t;
	using Uid = uint128_t;

	class IAccountServiceForAdministrator;
	class IAccountServiceForApplication;
	class IAccountServiceForSystemService;
	class IBaasAccessTokenAccessor;
}
namespace nn::account::baas {
	class IAdministrator;
	class IFloatingRegistrationRequest;
	class IGuestLoginRequest;
	class IManagerForApplication;
	class IManagerForSystemService;
}
namespace nn::account::detail {
	using Uuid = uint128_t;

	class IAsyncContext;
	class INotifier;
	class ISessionObject;
}
namespace nn::account::http {
	class IOAuthProcedure;
}
namespace nn::account::nas {
	using NasClientInfo = uint8_t;
	using NasUserBase = uint8_t;
	using NasUserBaseForApplication = uint8_t;
	using State = uint8_t;

	class IAuthorizationRequest;
	class IOAuthProcedureForExternalNsa;
	class IOAuthProcedureForNintendoAccountLinkage;
}
namespace nn::account::profile {
	using ProfileBase = uint8_t *; // uint8_t[0x38]
	using UserData = uint8_t;

	class IProfile;
	class IProfileEditor;
}
namespace nn::ahid {
	class ICtrlSession;
	class IReadSession;
	class IServerSession;
}
namespace nn::ahid::hdr {
	class ISession;
}
namespace nn::am {
	using AppletAttribute = uint8_t;
	using AppletMessage = uint32_t;
}
namespace nn::am::service {
	using AppletIdentityInfo = uint128_t;
	using AppletKind = uint64_t;
	using AppletProcessLaunchReason = uint32_t;
	using EmulatedButtonEvent = uint32_t;
	using LibraryAppletInfo = uint64_t;
	using WindowCreationOption = uint32_t;

	class IAllSystemAppletProxiesService;
	class IAppletAccessor;
	class IApplicationAccessor;
	class IApplicationCreator;
	class IApplicationFunctions;
	class IApplicationProxy;
	class IApplicationProxyService;
	class IAudioController;
	class ICommonStateGetter;
	class IDebugFunctions;
	class IDisplayController;
	class IGlobalStateController;
	class IHomeMenuFunctions;
	class ILibraryAppletAccessor;
	class ILibraryAppletCreator;
	class ILibraryAppletProxy;
	class ILibraryAppletSelfAccessor;
	class ILockAccessor;
	class IOverlayAppletProxy;
	class IOverlayFunctions;
	class IProcessWindingController;
	class ISelfController;
	class IStorage;
	class IStorageAccessor;
	class ISystemAppletProxy;
	class ITransferStorageAccessor;
	class IWindow;
	class IWindowController;
}
namespace nn::aocsrv::detail {
	class IAddOnContentManager;
}
namespace nn::apm {
	using EventTarget = uint32_t;
	using PerformanceConfiguration = uint32_t;
	using PerformanceMode = uint32_t;
	using ThrottlingState = uint8_t *; // uint8_t[0x28]

	class IManager;
	class IManagerPrivileged;
	class ISession;
	class ISystemManager;
}
namespace nn::applet {
	using AppletResourceUserId = uint64_t;
}
namespace nn::arp::detail {
	class IReader;
	class IRegistrar;
	class IWriter;
}
namespace nn::audio::detail {
	class IAudioDebugManager;
	class IAudioDevice;
	class IAudioIn;
	class IAudioInManager;
	class IAudioInManagerForApplet;
	class IAudioInManagerForDebugger;
	class IAudioOut;
	class IAudioOutManager;
	class IAudioOutManagerForApplet;
	class IAudioOutManagerForDebugger;
	class IAudioRenderer;
	class IAudioRendererManager;
	class IAudioRendererManagerForApplet;
	class IAudioRendererManagerForDebugger;
	class IFinalOutputRecorder;
	class IFinalOutputRecorderManager;
	class IFinalOutputRecorderManagerForApplet;
	class IFinalOutputRecorderManagerForDebugger;
}
namespace nn::audioctrl::detail {
	class IAudioController;
}
namespace nn::bcat {
	using DeliveryCacheDirectoryEntry = uint8_t;
	using Digest = uint128_t;
	using DirectoryName = uint8_t *; // uint8_t[0x20]
	using FileName = uint8_t *; // uint8_t[0x20]
	using PushNotificationLog = uint8_t;
	using TaskInfo = uint8_t;
}
namespace nn::bcat::detail {
	using DeliveryCacheProgressImpl = uint8_t;
}
namespace nn::bcat::detail::ipc {
	class IBcatService;
	class IDeliveryCacheDirectoryService;
	class IDeliveryCacheFileService;
	class IDeliveryCacheProgressService;
	class IDeliveryCacheStorageService;
	class IServiceCreator;
}
namespace nn::bgtc {
	class IStateControlService;
	class ITaskService;
}
namespace nn::bluetooth {
	using Address = uint8_t *; // uint8_t[6]

	class IBluetoothDriver;
}
namespace nn::bpc {
	class IBoardPowerControlManager;
	class IRtcManager;
}
namespace nn::bsdsocket::cfg {
	class ServerInterface;
}
namespace nn::btm {
	class IBtm;
	class IBtmDebug;
	class IBtmSystem;
	class IBtmSystemCore;
}
namespace nn::capsrv {
	using ApplicationAlbumEntry = uint8_t *; // uint8_t[0x20]
}
namespace nn::capsrv::detail {
	using ScreenShotAttributeEx0 = uint8_t *; // uint8_t[0x40]
}
namespace nn::capsrv::sf {
	class IAlbumAccessorService;
	class IAlbumControlService;
	class IScreenShotApplicationService;
	class IScreenShotControlService;
	class IScreenShotService;
}
namespace nn::cec {
	class ICecManager;
}
namespace nn::codec::detail {
	class IHardwareOpusDecoder;
	class IHardwareOpusDecoderManager;
}
namespace nn::erpt::sf {
	class IContext;
	class IManager;
	class IReport;
	class ISession;
}
namespace nn::err {
	using ErrorCode = uint64_t;
}
namespace nn::es {
	class IETicketService;
}
namespace nn::eth::sf {
	class IEthInterface;
	class IEthInterfaceGroup;
}
namespace nn::eupld::sf {
	class IControl;
	class IRequest;
}
namespace nn::fan::detail {
	class IController;
	class IManager;
}
namespace nn::fatalsrv {
	class IPrivateService;
	class IService;
}
namespace nn::fgm {
	using Module = uint32_t;
}
namespace nn::fgm::sf {
	class IDebugger;
	class IRequest;
	class ISession;
}
namespace nn::friends {
	using ApplicationInfo = uint128_t;
	using ExternalApplicationCatalog = uint8_t;
	using ExternalApplicationCatalogId = uint128_t;
	using FacedFriendRequestRegistrationKey = uint8_t *; // uint8_t[0x40]
	using FriendCode = uint8_t *; // uint8_t[0x20]
	using InAppScreenName = uint8_t;
	using MiiImageUrlParam = uint128_t;
	using MiiName = uint8_t *; // uint8_t[0x20]
	using NintendoNetworkIdUserInfo = uint8_t;
	using PlayHistoryRegistrationKey = uint8_t;
	using PlayHistoryStatistics = uint128_t;
	using Relationship = uint64_t;
	using RequestId = uint64_t;
	using Url = uint8_t *; // uint8_t[0xa0]
}
namespace nn::friends::detail {
	using BlockedUserImpl = uint8_t;
	using FriendCandidateImpl = uint8_t;
	using FriendDetailedInfoImpl = uint8_t;
	using FriendImpl = uint8_t;
	using FriendRequestImpl = uint8_t;
	using FriendSettingImpl = uint8_t;
	using NintendoNetworkIdFriendImpl = uint8_t;
	using PlayHistoryImpl = uint8_t;
	using ProfileExtraImpl = uint8_t;
	using ProfileImpl = uint8_t;
	using UserPresenceImpl = uint8_t;
	using UserPresenceViewImpl = uint8_t;
	using UserSettingImpl = uint8_t;
}
namespace nn::friends::detail::ipc {
	using SizedFriendFilter = uint128_t;
	using SizedNotificationInfo = uint128_t;

	class IFriendService;
	class INotificationService;
	class IServiceCreator;
}
namespace nn::fssrv::sf {
	using Partition = uint32_t;
	using SaveCreateStruct = uint8_t *; // uint8_t[0x40]
	using SaveStruct = uint8_t *; // uint8_t[0x40]

	class IDeviceOperator;
	class IDirectory;
	class IEventNotifier;
	class IFile;
	class IFileSystem;
	class IFileSystemProxy;
	class IFileSystemProxyForLoader;
	class IProgramRegistry;
	class ISaveDataInfoReader;
	class IStorage;
}
namespace nn::gpio {
	class IManager;
	class IPadSession;
}
namespace nn::hid {
	using BasicXpadId = uint32_t;
	using ConsoleSixAxisSensorHandle = uint32_t;
	using JoyXpadId = uint32_t;
	using NpadStyleTag = uint32_t;
	using SixAxisSensorHandle = uint32_t;
	using TouchState = uint8_t;
	using VibrationDeviceHandle = uint32_t;
	using VibrationDeviceInfoForIpc = uint64_t;
	using VibrationValue = uint128_t;

	class IActiveVibrationDeviceList;
	class IAppletResource;
	class IHidDebugServer;
	class IHidServer;
	class IHidSystemServer;
	class IHidTemporaryServer;
}
namespace nn::hid::debug {
	using BasicXpadAutoPilotState = uint8_t *; // uint8_t[0x1c]
	using CaptureButtonAutoPilotState = uint64_t;
	using DebugPadAutoPilotState = uint8_t *; // uint8_t[0x18]
	using HomeButtonAutoPilotState = uint64_t;
	using KeyboardAutoPilotState = uint8_t *; // uint8_t[0x28]
	using MouseAutoPilotState = uint8_t *; // uint8_t[0x1c]
	using SleepButtonAutoPilotState = uint64_t;
}
namespace nn::hid::system {
	using DeviceType = uint32_t;
	using FirmwareUpdateDeviceHandle = uint64_t;
	using FirmwareUpdateState = uint32_t;
	using FirmwareVersion = uint128_t;
	using InputSourceId = uint32_t;
	using KeyboardLockKeyEvent = uint32_t;
	using PlayReportControllerUsage = uint8_t;
	using RegisteredDevice = uint8_t;
	using UniquePadId = uint64_t;
	using UniqueSixAxisSensorHandle = uint32_t;
}
namespace nn::hid::tmp {
	using ConsoleSixAxisSensorCalibrationValues = uint8_t *; // uint8_t[0x18]
}
namespace nn::htc::tenv {
	class IService;
	class IServiceManager;
}
namespace nn::i2c {
	class IManager;
	class ISession;
}
namespace nn::idle::detail {
	class IPolicyManagerSystem;
}
namespace nn::irsensor {
	using ImageTransferProcessorState = uint128_t;
	using IrCameraHandle = uint32_t;
	using PackedClusteringProcessorConfig = uint8_t *; // uint8_t[0x28]
	using PackedDpdProcessorConfig = uint8_t *; // uint8_t[0xc]
	using PackedImageTransferProcessorConfig = uint8_t *; // uint8_t[0x18]
	using PackedMcuVersion = uint32_t;
	using PackedMomentProcessorConfig = uint8_t *; // uint8_t[0x20]
	using PackedTeraPluginProcessorConfig = uint64_t;

	class IIrSensorServer;
	class IIrSensorSystemServer;
}
namespace nn::lbl::detail {
	class ILblController;
}
namespace nn::ldn::detail {
	class IMonitorService;
	class IMonitorServiceCreator;
	class ISystemLocalCommunicationService;
	class ISystemServiceCreator;
	class IUserLocalCommunicationService;
	class IUserServiceCreator;
}
namespace nn::lm {
	class ILogService;
	class ILogger;
}
namespace nn::mii {
	using CharInfo = uint8_t *; // uint8_t[0x58]
	using CharInfoElement = uint8_t;
	using CreateId = uint128_t;
	using StoreData = uint8_t *; // uint8_t[0x44]
	using StoreDataElement = uint8_t;
}
namespace nn::mii::detail {
	class IDatabaseService;
	class IStaticService;
}
namespace nn::mmnv {
	class IRequest;
}
namespace nn::ncm {
	using ApplicationId = uint64_t;
	using ProgramId = uint64_t;
	using StorageId = uint8_t;
	using SystemApplicationId = uint64_t;
}
namespace nn::ncm::detail {
	class INcmInterface;
	class INcmInterface4Unknown;
	class INcmInterface5Unknown;
	class LocationResolverInterface;
}
namespace nn::news::detail::ipc {
	class INewlyArrivedEventHolder;
	class INewsDataService;
	class INewsDatabaseService;
	class INewsService;
	class IOverwriteEventHolder;
	class IServiceCreator;
}
namespace nn::nfc::am::detail {
	class IAm;
	class IAmManager;
}
namespace nn::nfc::detail {
	class ISystem;
	class ISystemManager;
	class IUser;
	class IUserManager;
}
namespace nn::nfc::mifare::detail {
	class IUser;
	class IUserManager;
}
namespace nn::nfp::detail {
	class IDebug;
	class IDebugManager;
	class ISystem;
	class ISystemManager;
	class IUser;
	class IUserManager;
}
namespace nn::nifm {
	using AdditionalInfo = uint8_t;
	using ClientId = uint8_t;
	using DnsSetting = uint8_t *; // uint8_t[9]
	using IpAddressSetting = uint8_t *; // uint8_t[0xd]
	using IpSettingData = uint8_t;
	using IpV4Address = uint32_t;
	using Requirement = uint8_t *; // uint8_t[0x24]
	using SsidListVersion = uint128_t;
	using TelemetryInfo = uint8_t;
}
namespace nn::nifm::detail {
	class IGeneralService;
	class INetworkProfile;
	class IRequest;
	class IScanRequest;
	class IStaticService;
}
namespace nn::nifm::detail::sf {
	using AccessPointData = uint8_t;
	using InternetConnectionStatus = uint8_t *; // uint8_t[3]
	using NetworkInterfaceInfo = uint8_t;
	using NetworkProfileBasicInfo = uint8_t;
	using NetworkProfileData = uint8_t;
}
namespace nn::nim::detail {
	class IAsyncData;
	class IAsyncProgressResult;
	class IAsyncResult;
	class IAsyncValue;
	class INetworkInstallManager;
	class IShopServiceManager;
}
namespace nn::npns {
	using NotificationToken = uint8_t *; // uint8_t[0x28]

	class INpnsSystem;
	class INpnsUser;
	class Weird;
}
namespace nn::ns {
	using ApplicationControlProperty = uint8_t;
}
namespace nn::ns::detail {
	class IAccountProxyInterface;
	class IApplicationManagerInterface;
	class IAsyncResult;
	class IAsyncValue;
	class IContentManagementInterface;
	class IDevelopInterface;
	class IDocumentInterface;
	class IDownloadTaskInterface;
	class IFactoryResetInterface;
	class IGameCardStopper;
	class IProgressAsyncResult;
	class IProgressMonitorForDeleteUserSaveDataAll;
	class IRequestServerStopper;
	class IServiceGetterInterface;
	class ISystemUpdateControl;
	class ISystemUpdateInterface;
	class IVulnerabilityManagerInterface;
}
namespace nn::nsd::detail {
	class IManager;
}
namespace nn::ntc::detail::service {
	class IEnsureNetworkClockAvailabilityService;
	class IStaticService;
}
namespace nn::oe {
	using DisplayVersion = uint128_t;
}
namespace nn::omm::detail {
	class IOperationModeManager;
}
namespace nn::ovln {
	class IReceiver;
	class IReceiverService;
	class ISender;
	class ISenderService;
}
namespace nn::pcie::detail {
	class IManager;
	class ISession;
}
namespace nn::pctl {
	using FreeCommunicationApplicationInfo = uint8_t;
	using InquiryCode = uint8_t *; // uint8_t[0x20]
	using PlayTimerSettings = uint8_t *; // uint8_t[0x34]
	using SafetyLevelSettings = uint8_t *; // uint8_t[3]
}
namespace nn::pctl::detail {
	using AsyncData = uint64_t;
	using PairingAccountInfoBase = uint128_t;
	using PairingInfoBase = uint128_t;
}
namespace nn::pctl::detail::ipc {
	class IParentalControlService;
	class IParentalControlServiceFactory;
}
namespace nn::pcv {
	using ModuleState = uint8_t *; // uint8_t[0xc]
	using PowerControlTarget = uint32_t;
	using PowerDomainState = uint8_t;
	using TemperatureThreshold = uint8_t;

	class IArbitrationManager;
	class IImmediateManager;
}
namespace nn::pcv::detail {
	class IPcvService;
}
namespace nn::pdm::detail {
	class INotifyService;
	class IQueryService;
}
namespace nn::pinmux {
	class IManager;
	class ISession;
}
namespace nn::pl::detail {
	class ISharedFontManager;
}
namespace nn::prepo::detail::ipc {
	class IPrepoService;
}
namespace nn::psc::sf {
	class IPmControl;
	class IPmModule;
	class IPmService;
}
namespace nn::psm {
	class IPsmServer;
	class IPsmSession;
}
namespace nn::pwm {
	class IChannelSession;
	class IManager;
}
namespace nn::ro::detail {
	class IDebugMonitorInterface;
	class ILdrShellInterface;
	class IRoInterface;
}
namespace nn::sasbus {
	class IManager;
	class ISession;
}
namespace nn::settings {
	using LanguageCode = uint64_t;
	using SettingsItemKey = uint8_t;
	using SettingsName = uint8_t;

	class IFactorySettingsServer;
	class IFirmwareDebugSettingsServer;
	class ISettingsItemKeyIterator;
	class ISettingsServer;
	class ISystemSettingsServer;
}
namespace nn::settings::factory {
	using AccelerometerOffset = uint8_t *; // uint8_t[6]
	using AccelerometerScale = uint8_t *; // uint8_t[6]
	using BatteryLot = uint8_t *; // uint8_t[0x18]
	using BdAddress = uint8_t *; // uint8_t[6]
	using ConfigurationId1 = uint8_t *; // uint8_t[0x1e]
	using CountryCode = uint8_t;
	using EccB233DeviceCertificate = uint8_t;
	using EccB233DeviceKey = uint8_t *; // uint8_t[0x54]
	using GameCardCertificate = uint8_t;
	using GameCardKey = uint8_t;
	using GyroscopeOffset = uint8_t *; // uint8_t[6]
	using GyroscopeScale = uint8_t *; // uint8_t[6]
	using MacAddress = uint8_t *; // uint8_t[6]
	using Rsa2048DeviceCertificate = uint8_t;
	using Rsa2048DeviceKey = uint8_t;
	using SerialNumber = uint8_t *; // uint8_t[0x18]
	using SpeakerParameter = uint8_t *; // uint8_t[0x5a]
	using SslCertificate = uint8_t;
	using SslKey = uint8_t;
}
namespace nn::settings::system {
	using AccountNotificationSettings = uint8_t;
	using AccountSettings = uint32_t;
	using AudioVolume = uint64_t;
	using BacklightSettings = uint8_t *; // uint8_t[0x28]
	using BacklightSettingsEx = uint8_t *; // uint8_t[0x2c]
	using BatteryLot = uint8_t *; // uint8_t[0x18]
	using BluetoothDevicesSettings = uint8_t;
	using DataDeletionSettings = uint64_t;
	using DeviceNickName = uint8_t;
	using Edid = uint8_t;
	using EulaVersion = uint8_t;
	using FatalDirtyFlag = uint128_t;
	using FirmwareVersion = uint8_t;
	using InitialLaunchSettings = uint8_t *; // uint8_t[0x20]
	using NetworkSettings = uint8_t;
	using NotificationSettings = uint8_t *; // uint8_t[0x18]
	using NxControllerSettings = uint8_t;
	using PtmFuelGaugeParameter = uint8_t *; // uint8_t[0x18]
	using SerialNumber = uint8_t *; // uint8_t[0x18]
	using SleepSettings = uint8_t *; // uint8_t[0xc]
	using TelemetryDirtyFlag = uint128_t;
	using TvSettings = uint8_t *; // uint8_t[0x20]
}
namespace nn::sm::detail {
	class IManagerInterface;
	class IUserInterface;
}
namespace nn::socket::resolver {
	class IResolver;
}
namespace nn::socket::sf {
	class IClient;
}
namespace nn::spl::detail {
	class IRandomInterface;
}
namespace nn::spsm::detail {
	class IPowerStateInterface;
}
namespace nn::ssl::sf {
	using CertificateFormat = uint32_t;
	using ContextOption = uint32_t;
	using InternalPki = uint32_t;
	using IoMode = uint32_t;
	using OptionType = uint32_t;
	using PollEvent = uint32_t;
	using RenegotiationMode = uint32_t;
	using SessionCacheMode = uint32_t;
	using SslVersion = uint32_t;
	using VerifyOption = uint32_t;

	class ISslConnection;
	class ISslContext;
	class ISslService;
}
namespace nn::tc {
	class IManager;
}
namespace nn::time {
	using CalendarTime = uint64_t;
	using LocationName = uint8_t *; // uint8_t[0x24]
	using PosixTime = uint64_t;
	using SteadyClockTimePoint = uint8_t *; // uint8_t[0x18]
	using SystemClockContext = uint8_t *; // uint8_t[0x20]
	using TimeZoneRule = uint8_t;
	using TimeZoneRuleVersion = uint128_t;
}
namespace nn::time::sf {
	using CalendarAdditionalInfo = uint8_t *; // uint8_t[0x18]
}
namespace nn::timesrv::detail::service {
	class IStaticService;
	class ISteadyClock;
	class ISystemClock;
	class ITimeZoneService;
}
namespace nn::tma {
	class IHtcManager;
	class IHtcsManager;
	class ISocket;
}
namespace nn::ts::server {
	class IMeasurementServer;
}
namespace nn::uart {
	class IManager;
	class IPortSession;
}
namespace nn::usb::ds {
	class IDsEndpoint;
	class IDsInterface;
	class IDsService;
}
namespace nn::usb::hs {
	class IClientEpSession;
	class IClientIfSession;
	class IClientRootSession;
}
namespace nn::usb::pd::detail {
	class IPdCradleManager;
	class IPdCradleSession;
	class IPdManager;
	class IPdSession;
}
namespace nn::usb::pm {
	class IPmService;
}
namespace nn::util {
	using Unorm8x4 = uint32_t;
	using Uuid = uint128_t;
}
namespace nn::vi {
	using DisplayInfo = uint8_t;
	using DisplayModeInfo = uint128_t;
	using DisplayName = uint8_t *; // uint8_t[0x40]
	using ProxyName = uint64_t;
}
namespace nn::visrv::sf {
	class IApplicationDisplayService;
	class IApplicationRootService;
	class IManagerDisplayService;
	class IManagerRootService;
	class ISystemDisplayService;
	class ISystemRootService;
}
namespace nn::wlan::detail {
	class IInfraManager;
	class ILocalGetActionFrame;
	class ILocalGetFrame;
	class ILocalManager;
	class ISocketGetFrame;
	class ISocketManager;
}
namespace nn::xcd::detail {
	class ISystemServer;
}
namespace nns::hosbinder {
	class IHOSBinderDriver;
}
namespace nns::nvdrv {
	class INvDrvDebugFSServices;
	class INvDrvServices;
}
namespace nv::gemcontrol {
	class INvGemControl;
}
namespace nv::gemcoredump {
	class INvGemCoreDump;
}

//// namespace None {
	class SmService {
	public:
		SmService();
		uint32_t GetService(IN ServiceName name, OUT IPipe * _1);
		uint32_t Initialize();
		uint32_t RegisterService(IN ServiceName name, OUT NPort * _1);
		uint32_t UnregisterService(IN ServiceName name);
	};
//// }
#ifdef DEFINE_CALLERS
uint32_t SmService::GetService(IN ServiceName name, OUT IPipe * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new IPipe(resp.move_handles[0]);
	return ret;
}
uint32_t SmService::Initialize() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t SmService::RegisterService(IN ServiceName name, OUT NPort * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new NPort(resp.move_handles[0]);
	return ret;
}
uint32_t SmService::UnregisterService(IN ServiceName name) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace Pm {
	class Bm {
	public:
		Bm();
		uint32_t EnableMaintenanceMode();
		uint32_t Init(OUT uint64_t& _0);
	};
	class Shell {
	public:
		Shell();
		uint32_t GetProcessEventWaiter(OUT KObject * _0);
		uint32_t LaunchTitle(IN uint64_t _0, IN nn::ApplicationId tid);
	};
}
#ifdef DEFINE_CALLERS
uint32_t Pm::Bm::EnableMaintenanceMode() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t Pm::Bm::Init(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t Pm::Shell::GetProcessEventWaiter(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t Pm::Shell::LaunchTitle(IN uint64_t _0, IN nn::ApplicationId tid) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::account {
	class IAccountServiceForAdministrator {
	public:
		IAccountServiceForAdministrator();
		uint32_t AuthenticateServiceAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t BeginUserRegistration(OUT nn::account::Uid& _0);
		uint32_t CancelUserRegistration(IN nn::account::Uid _0);
		uint32_t ClearSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1);
		uint32_t CompleteUserRegistration(IN nn::account::Uid _0);
		uint32_t CompleteUserRegistrationForcibly(IN nn::account::Uid _0);
		uint32_t CreateFloatingRegistrationRequest(IN uint32_t _0, IN KObject * _1, OUT nn::account::baas::IFloatingRegistrationRequest * _2);
		uint32_t DebugInvalidateTokenCacheForUser(IN nn::account::Uid _0);
		uint32_t DebugSetUserStateClose(IN nn::account::Uid _0);
		uint32_t DebugSetUserStateOpen(IN nn::account::Uid _0);
		uint32_t DeleteUser(IN nn::account::Uid _0);
		uint32_t GetBaasAccountAdministrator(IN nn::account::Uid _0, OUT nn::account::baas::IAdministrator * _1);
		uint32_t GetBaasAccountManagerForSystemService(IN nn::account::Uid _0, OUT nn::account::baas::IManagerForSystemService * _1);
		uint32_t GetBaasUserAvailabilityChangeNotifier(OUT nn::account::detail::INotifier * _0);
		uint32_t GetLastOpenedUser(OUT nn::account::Uid& _0);
		uint32_t GetProfile(IN nn::account::Uid _0, OUT nn::account::profile::IProfile * _1);
		uint32_t GetProfileDigest(IN nn::account::Uid _0, OUT nn::account::ProfileDigest& _1);
		uint32_t GetProfileEditor(IN nn::account::Uid _0, OUT nn::account::profile::IProfileEditor * _1);
		uint32_t GetProfileUpdateNotifier(OUT nn::account::detail::INotifier * _0);
		uint32_t GetUserCount(OUT int32_t& _0);
		uint32_t GetUserExistence(IN nn::account::Uid _0, OUT bool& _1);
		uint32_t GetUserLastOpenedApplication(IN nn::account::Uid _0, OUT uint32_t& _1, OUT nn::ApplicationId& _2);
		uint32_t GetUserRegistrationNotifier(OUT nn::account::detail::INotifier * _0);
		uint32_t GetUserStateChangeNotifier(OUT nn::account::detail::INotifier * _0);
		uint32_t IsUserRegistrationRequestPermitted(IN uint64_t _0, IN gpid _1, OUT bool& _2);
		uint32_t ListAllUsers(OUT nn::account::Uid * _0, guint _0_size);
		uint32_t ListOpenUsers(OUT nn::account::Uid * _0, guint _0_size);
		uint32_t LoadSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t ProxyProcedureForFloatingRegistrationWithNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::nas::IOAuthProcedureForExternalNsa * _1);
		uint32_t ProxyProcedureForGuestLoginWithNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::nas::IOAuthProcedureForExternalNsa * _1);
		uint32_t SetUserPosition(IN int32_t _0, IN nn::account::Uid _1);
		uint32_t StoreSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1, IN uint8_t * _2, guint _2_size);
		uint32_t SuspendBackgroundDaemon(OUT nn::account::detail::ISessionObject * _0);
		uint32_t TrySelectUserWithoutInteraction(IN bool _0, OUT nn::account::Uid& _1);
	};
	class IAccountServiceForApplication {
	public:
		IAccountServiceForApplication();
		uint32_t AuthenticateApplicationAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t ClearSaveDataThumbnail(IN nn::account::Uid _0);
		uint32_t CreateGuestLoginRequest(IN uint32_t _0, IN KObject * _1, OUT nn::account::baas::IGuestLoginRequest * _2);
		uint32_t GetBaasAccountManagerForApplication(IN nn::account::Uid _0, OUT nn::account::baas::IManagerForApplication * _1);
		uint32_t GetLastOpenedUser(OUT nn::account::Uid& _0);
		uint32_t GetProfile(IN nn::account::Uid _0, OUT nn::account::profile::IProfile * _1);
		uint32_t GetProfileDigest(IN nn::account::Uid _0, OUT nn::account::ProfileDigest& _1);
		uint32_t GetUserCount(OUT int32_t& _0);
		uint32_t GetUserExistence(IN nn::account::Uid _0, OUT bool& _1);
		uint32_t InitializeApplicationInfo(IN uint64_t _0, IN gpid _1);
		uint32_t IsUserRegistrationRequestPermitted(IN uint64_t _0, IN gpid _1, OUT bool& _2);
		uint32_t ListAllUsers(OUT nn::account::Uid * _0, guint _0_size);
		uint32_t ListOpenUsers(OUT nn::account::Uid * _0, guint _0_size);
		uint32_t StoreSaveDataThumbnail(IN nn::account::Uid _0, IN uint8_t * _1, guint _1_size);
		uint32_t TrySelectUserWithoutInteraction(IN bool _0, OUT nn::account::Uid& _1);
	};
	class IAccountServiceForSystemService {
	public:
		IAccountServiceForSystemService();
		uint32_t ClearSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1);
		uint32_t DebugInvalidateTokenCacheForUser(IN nn::account::Uid _0);
		uint32_t DebugSetUserStateClose(IN nn::account::Uid _0);
		uint32_t DebugSetUserStateOpen(IN nn::account::Uid _0);
		uint32_t GetBaasAccountManagerForSystemService(IN nn::account::Uid _0, OUT nn::account::baas::IManagerForSystemService * _1);
		uint32_t GetBaasUserAvailabilityChangeNotifier(OUT nn::account::detail::INotifier * _0);
		uint32_t GetLastOpenedUser(OUT nn::account::Uid& _0);
		uint32_t GetProfile(IN nn::account::Uid _0, OUT nn::account::profile::IProfile * _1);
		uint32_t GetProfileDigest(IN nn::account::Uid _0, OUT nn::account::ProfileDigest& _1);
		uint32_t GetProfileUpdateNotifier(OUT nn::account::detail::INotifier * _0);
		uint32_t GetUserCount(OUT int32_t& _0);
		uint32_t GetUserExistence(IN nn::account::Uid _0, OUT bool& _1);
		uint32_t GetUserLastOpenedApplication(IN nn::account::Uid _0, OUT uint32_t& _1, OUT nn::ApplicationId& _2);
		uint32_t GetUserRegistrationNotifier(OUT nn::account::detail::INotifier * _0);
		uint32_t GetUserStateChangeNotifier(OUT nn::account::detail::INotifier * _0);
		uint32_t IsUserRegistrationRequestPermitted(IN uint64_t _0, IN gpid _1, OUT bool& _2);
		uint32_t ListAllUsers(OUT nn::account::Uid * _0, guint _0_size);
		uint32_t ListOpenUsers(OUT nn::account::Uid * _0, guint _0_size);
		uint32_t LoadSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t StoreSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1, IN uint8_t * _2, guint _2_size);
		uint32_t TrySelectUserWithoutInteraction(IN bool _0, OUT nn::account::Uid& _1);
	};
	class IBaasAccessTokenAccessor {
	public:
		IBaasAccessTokenAccessor();
		uint32_t EnsureCacheAsync(IN nn::account::Uid _0, OUT nn::account::detail::IAsyncContext * _1);
		uint32_t GetDeviceAccountId(IN nn::account::Uid _0, OUT uint64_t& _1);
		uint32_t LoadCache(IN nn::account::Uid _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t RegisterNotificationTokenAsync(IN nn::npns::NotificationToken _0, IN nn::account::Uid _1, OUT nn::account::detail::IAsyncContext * _2);
		uint32_t UnregisterNotificationTokenAsync(IN nn::account::Uid _0, OUT nn::account::detail::IAsyncContext * _1);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::account::IAccountServiceForAdministrator::AuthenticateServiceAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::BeginUserRegistration(OUT nn::account::Uid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::CancelUserRegistration(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::ClearSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::CompleteUserRegistration(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::CompleteUserRegistrationForcibly(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::CreateFloatingRegistrationRequest(IN uint32_t _0, IN KObject * _1, OUT nn::account::baas::IFloatingRegistrationRequest * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::account::baas::IFloatingRegistrationRequest(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::DebugInvalidateTokenCacheForUser(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::DebugSetUserStateClose(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::DebugSetUserStateOpen(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::DeleteUser(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetBaasAccountAdministrator(IN nn::account::Uid _0, OUT nn::account::baas::IAdministrator * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::baas::IAdministrator(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetBaasAccountManagerForSystemService(IN nn::account::Uid _0, OUT nn::account::baas::IManagerForSystemService * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::baas::IManagerForSystemService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetBaasUserAvailabilityChangeNotifier(OUT nn::account::detail::INotifier * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::INotifier(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetLastOpenedUser(OUT nn::account::Uid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetProfile(IN nn::account::Uid _0, OUT nn::account::profile::IProfile * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::profile::IProfile(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetProfileDigest(IN nn::account::Uid _0, OUT nn::account::ProfileDigest& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetProfileEditor(IN nn::account::Uid _0, OUT nn::account::profile::IProfileEditor * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::profile::IProfileEditor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetProfileUpdateNotifier(OUT nn::account::detail::INotifier * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::INotifier(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetUserCount(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetUserExistence(IN nn::account::Uid _0, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetUserLastOpenedApplication(IN nn::account::Uid _0, OUT uint32_t& _1, OUT nn::ApplicationId& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetUserRegistrationNotifier(OUT nn::account::detail::INotifier * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::INotifier(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::GetUserStateChangeNotifier(OUT nn::account::detail::INotifier * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::INotifier(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::IsUserRegistrationRequestPermitted(IN uint64_t _0, IN gpid _1, OUT bool& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::ListAllUsers(OUT nn::account::Uid * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::ListOpenUsers(OUT nn::account::Uid * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::LoadSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::ProxyProcedureForFloatingRegistrationWithNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::nas::IOAuthProcedureForExternalNsa * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::nas::IOAuthProcedureForExternalNsa(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::ProxyProcedureForGuestLoginWithNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::nas::IOAuthProcedureForExternalNsa * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::nas::IOAuthProcedureForExternalNsa(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::SetUserPosition(IN int32_t _0, IN nn::account::Uid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::StoreSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::SuspendBackgroundDaemon(OUT nn::account::detail::ISessionObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::ISessionObject(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForAdministrator::TrySelectUserWithoutInteraction(IN bool _0, OUT nn::account::Uid& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::AuthenticateApplicationAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::ClearSaveDataThumbnail(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::CreateGuestLoginRequest(IN uint32_t _0, IN KObject * _1, OUT nn::account::baas::IGuestLoginRequest * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::account::baas::IGuestLoginRequest(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::GetBaasAccountManagerForApplication(IN nn::account::Uid _0, OUT nn::account::baas::IManagerForApplication * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::baas::IManagerForApplication(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::GetLastOpenedUser(OUT nn::account::Uid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::GetProfile(IN nn::account::Uid _0, OUT nn::account::profile::IProfile * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::profile::IProfile(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::GetProfileDigest(IN nn::account::Uid _0, OUT nn::account::ProfileDigest& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::GetUserCount(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::GetUserExistence(IN nn::account::Uid _0, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::InitializeApplicationInfo(IN uint64_t _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::IsUserRegistrationRequestPermitted(IN uint64_t _0, IN gpid _1, OUT bool& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::ListAllUsers(OUT nn::account::Uid * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::ListOpenUsers(OUT nn::account::Uid * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::StoreSaveDataThumbnail(IN nn::account::Uid _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IAccountServiceForApplication::TrySelectUserWithoutInteraction(IN bool _0, OUT nn::account::Uid& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::ClearSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::DebugInvalidateTokenCacheForUser(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::DebugSetUserStateClose(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::DebugSetUserStateOpen(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::GetBaasAccountManagerForSystemService(IN nn::account::Uid _0, OUT nn::account::baas::IManagerForSystemService * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::baas::IManagerForSystemService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::GetBaasUserAvailabilityChangeNotifier(OUT nn::account::detail::INotifier * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::INotifier(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::GetLastOpenedUser(OUT nn::account::Uid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::GetProfile(IN nn::account::Uid _0, OUT nn::account::profile::IProfile * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::profile::IProfile(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::GetProfileDigest(IN nn::account::Uid _0, OUT nn::account::ProfileDigest& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::GetProfileUpdateNotifier(OUT nn::account::detail::INotifier * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::INotifier(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::GetUserCount(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::GetUserExistence(IN nn::account::Uid _0, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::GetUserLastOpenedApplication(IN nn::account::Uid _0, OUT uint32_t& _1, OUT nn::ApplicationId& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::GetUserRegistrationNotifier(OUT nn::account::detail::INotifier * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::INotifier(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::GetUserStateChangeNotifier(OUT nn::account::detail::INotifier * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::INotifier(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::IsUserRegistrationRequestPermitted(IN uint64_t _0, IN gpid _1, OUT bool& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::ListAllUsers(OUT nn::account::Uid * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::ListOpenUsers(OUT nn::account::Uid * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::LoadSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::StoreSaveDataThumbnail(IN nn::account::Uid _0, IN nn::ApplicationId _1, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IAccountServiceForSystemService::TrySelectUserWithoutInteraction(IN bool _0, OUT nn::account::Uid& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IBaasAccessTokenAccessor::EnsureCacheAsync(IN nn::account::Uid _0, OUT nn::account::detail::IAsyncContext * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IBaasAccessTokenAccessor::GetDeviceAccountId(IN nn::account::Uid _0, OUT uint64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::IBaasAccessTokenAccessor::LoadCache(IN nn::account::Uid _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::IBaasAccessTokenAccessor::RegisterNotificationTokenAsync(IN nn::npns::NotificationToken _0, IN nn::account::Uid _1, OUT nn::account::detail::IAsyncContext * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::IBaasAccessTokenAccessor::UnregisterNotificationTokenAsync(IN nn::account::Uid _0, OUT nn::account::detail::IAsyncContext * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::account::baas {
	class IAdministrator {
	public:
		IAdministrator();
		uint32_t CheckAvailability();
		uint32_t CreateAuthorizationRequest(IN uint32_t _0, IN KObject * _1, IN nn::account::nas::NasClientInfo * _2, guint _2_size, IN nn::account::NintendoAccountAuthorizationRequestParameters * _3, guint _3_size, OUT nn::account::nas::IAuthorizationRequest * _4);
		uint32_t CreateProcedureToLinkNnidWithNintendoAccount(OUT nn::account::http::IOAuthProcedure * _0);
		uint32_t CreateProcedureToLinkWithNintendoAccount(OUT nn::account::nas::IOAuthProcedureForNintendoAccountLinkage * _0);
		uint32_t CreateProcedureToUpdateLinkageStateOfNintendoAccount(OUT nn::account::http::IOAuthProcedure * _0);
		uint32_t DebugSetAvailabilityErrorDetail(IN uint32_t _0);
		uint32_t DebugUnlinkNintendoAccountAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t DeleteRegistrationInfoLocally();
		uint32_t EnsureIdTokenCacheAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t GetAccountId(OUT nn::account::NetworkServiceAccountId& _0);
		uint32_t GetNintendoAccountId(OUT nn::account::NintendoAccountId& _0);
		uint32_t GetNintendoAccountUserResourceCache(OUT nn::account::NintendoAccountId& _0, OUT nn::account::nas::NasUserBase * _1, guint _1_size, OUT uint8_t * _2, guint _2_size);
		uint32_t IsLinkedWithNintendoAccount(OUT bool& _0);
		uint32_t IsRegistered(OUT bool& _0);
		uint32_t LoadIdTokenCache(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t ProxyProcedureToAcquireApplicationAuthorizationForNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::http::IOAuthProcedure * _1);
		uint32_t RefreshNintendoAccountUserResourceCacheAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t RefreshNintendoAccountUserResourceCacheAsyncIfSecondsElapsed(IN uint32_t _0, OUT bool& _1, OUT nn::account::detail::IAsyncContext * _2);
		uint32_t RegisterAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t ResumeProcedureToLinkNnidWithNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::http::IOAuthProcedure * _1);
		uint32_t ResumeProcedureToLinkWithNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::nas::IOAuthProcedureForNintendoAccountLinkage * _1);
		uint32_t ResumeProcedureToUpdateLinkageStateOfNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::http::IOAuthProcedure * _1);
		uint32_t SetSystemProgramIdentification(IN uint64_t _0, IN gpid _1, IN nn::account::SystemProgramIdentification * _2, guint _2_size);
		uint32_t SynchronizeProfileAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t SynchronizeProfileAsyncIfSecondsElapsed(IN uint32_t _0, OUT bool& _1, OUT nn::account::detail::IAsyncContext * _2);
		uint32_t UnregisterAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t UploadProfileAsync(OUT nn::account::detail::IAsyncContext * _0);
	};
	class IFloatingRegistrationRequest {
	public:
		IFloatingRegistrationRequest();
		uint32_t EnsureIdTokenCacheAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t GetAccountId(OUT nn::account::NetworkServiceAccountId& _0);
		uint32_t GetLinkedNintendoAccountId(OUT nn::account::NintendoAccountId& _0);
		uint32_t GetNickname(OUT int8_t * _0, guint _0_size);
		uint32_t GetProfileImage(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetSessionId(OUT nn::account::detail::Uuid& _0);
		uint32_t LoadIdTokenCache(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t RegisterAsync(OUT nn::account::Uid& _0, OUT nn::account::detail::IAsyncContext * _1);
		uint32_t RegisterWithUidAsync(IN nn::account::Uid _0, OUT nn::account::detail::IAsyncContext * _1);
		uint32_t SetSystemProgramIdentification(IN uint64_t _0, IN gpid _1, IN nn::account::SystemProgramIdentification * _2, guint _2_size);
	};
	class IGuestLoginRequest {
	public:
		IGuestLoginRequest();
		uint32_t GetAccountId(OUT nn::account::NetworkServiceAccountId& _0);
		uint32_t GetLinkedNintendoAccountId(OUT nn::account::NintendoAccountId& _0);
		uint32_t GetNickname(OUT int8_t * _0, guint _0_size);
		uint32_t GetProfileImage(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetSessionId(OUT nn::account::detail::Uuid& _0);
		uint32_t LoadIdTokenCache(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
	};
	class IManagerForApplication {
	public:
		IManagerForApplication();
		uint32_t CheckAvailability();
		uint32_t CreateAuthorizationRequest(IN uint32_t _0, IN KObject * _1, IN nn::account::NintendoAccountAuthorizationRequestParameters * _2, guint _2_size, OUT nn::account::nas::IAuthorizationRequest * _3);
		uint32_t EnsureIdTokenCacheAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t GetAccountId(OUT nn::account::NetworkServiceAccountId& _0);
		uint32_t GetNintendoAccountUserResourceCacheForApplication(OUT nn::account::NintendoAccountId& _0, OUT nn::account::nas::NasUserBaseForApplication * _1, guint _1_size, OUT uint8_t * _2, guint _2_size);
		uint32_t LoadIdTokenCache(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
	};
	class IManagerForSystemService {
	public:
		IManagerForSystemService();
		uint32_t CheckAvailability();
		uint32_t CreateAuthorizationRequest(IN uint32_t _0, IN KObject * _1, IN nn::account::nas::NasClientInfo * _2, guint _2_size, IN nn::account::NintendoAccountAuthorizationRequestParameters * _3, guint _3_size, OUT nn::account::nas::IAuthorizationRequest * _4);
		uint32_t EnsureIdTokenCacheAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t GetAccountId(OUT nn::account::NetworkServiceAccountId& _0);
		uint32_t GetNintendoAccountId(OUT nn::account::NintendoAccountId& _0);
		uint32_t GetNintendoAccountUserResourceCache(OUT nn::account::NintendoAccountId& _0, OUT nn::account::nas::NasUserBase * _1, guint _1_size, OUT uint8_t * _2, guint _2_size);
		uint32_t LoadIdTokenCache(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t RefreshNintendoAccountUserResourceCacheAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t RefreshNintendoAccountUserResourceCacheAsyncIfSecondsElapsed(IN uint32_t _0, OUT bool& _1, OUT nn::account::detail::IAsyncContext * _2);
		uint32_t SetSystemProgramIdentification(IN uint64_t _0, IN gpid _1, IN nn::account::SystemProgramIdentification * _2, guint _2_size);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::account::baas::IAdministrator::CheckAvailability() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::CreateAuthorizationRequest(IN uint32_t _0, IN KObject * _1, IN nn::account::nas::NasClientInfo * _2, guint _2_size, IN nn::account::NintendoAccountAuthorizationRequestParameters * _3, guint _3_size, OUT nn::account::nas::IAuthorizationRequest * _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	_4 OMG = new nn::account::nas::IAuthorizationRequest(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::CreateProcedureToLinkNnidWithNintendoAccount(OUT nn::account::http::IOAuthProcedure * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::http::IOAuthProcedure(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::CreateProcedureToLinkWithNintendoAccount(OUT nn::account::nas::IOAuthProcedureForNintendoAccountLinkage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::nas::IOAuthProcedureForNintendoAccountLinkage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::CreateProcedureToUpdateLinkageStateOfNintendoAccount(OUT nn::account::http::IOAuthProcedure * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::http::IOAuthProcedure(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::DebugSetAvailabilityErrorDetail(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::DebugUnlinkNintendoAccountAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::DeleteRegistrationInfoLocally() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::EnsureIdTokenCacheAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::GetAccountId(OUT nn::account::NetworkServiceAccountId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::GetNintendoAccountId(OUT nn::account::NintendoAccountId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::GetNintendoAccountUserResourceCache(OUT nn::account::NintendoAccountId& _0, OUT nn::account::nas::NasUserBase * _1, guint _1_size, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::account::baas::IAdministrator::IsLinkedWithNintendoAccount(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::IsRegistered(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::LoadIdTokenCache(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::baas::IAdministrator::ProxyProcedureToAcquireApplicationAuthorizationForNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::http::IOAuthProcedure * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::http::IOAuthProcedure(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::RefreshNintendoAccountUserResourceCacheAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::RefreshNintendoAccountUserResourceCacheAsyncIfSecondsElapsed(IN uint32_t _0, OUT bool& _1, OUT nn::account::detail::IAsyncContext * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::RegisterAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::ResumeProcedureToLinkNnidWithNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::http::IOAuthProcedure * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::http::IOAuthProcedure(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::ResumeProcedureToLinkWithNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::nas::IOAuthProcedureForNintendoAccountLinkage * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::nas::IOAuthProcedureForNintendoAccountLinkage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::ResumeProcedureToUpdateLinkageStateOfNintendoAccount(IN nn::account::detail::Uuid _0, OUT nn::account::http::IOAuthProcedure * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::http::IOAuthProcedure(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::SetSystemProgramIdentification(IN uint64_t _0, IN gpid _1, IN nn::account::SystemProgramIdentification * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::baas::IAdministrator::SynchronizeProfileAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::SynchronizeProfileAsyncIfSecondsElapsed(IN uint32_t _0, OUT bool& _1, OUT nn::account::detail::IAsyncContext * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::UnregisterAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IAdministrator::UploadProfileAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IFloatingRegistrationRequest::EnsureIdTokenCacheAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IFloatingRegistrationRequest::GetAccountId(OUT nn::account::NetworkServiceAccountId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IFloatingRegistrationRequest::GetLinkedNintendoAccountId(OUT nn::account::NintendoAccountId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IFloatingRegistrationRequest::GetNickname(OUT int8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::baas::IFloatingRegistrationRequest::GetProfileImage(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::baas::IFloatingRegistrationRequest::GetSessionId(OUT nn::account::detail::Uuid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IFloatingRegistrationRequest::LoadIdTokenCache(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::baas::IFloatingRegistrationRequest::RegisterAsync(OUT nn::account::Uid& _0, OUT nn::account::detail::IAsyncContext * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IFloatingRegistrationRequest::RegisterWithUidAsync(IN nn::account::Uid _0, OUT nn::account::detail::IAsyncContext * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IFloatingRegistrationRequest::SetSystemProgramIdentification(IN uint64_t _0, IN gpid _1, IN nn::account::SystemProgramIdentification * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::baas::IGuestLoginRequest::GetAccountId(OUT nn::account::NetworkServiceAccountId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IGuestLoginRequest::GetLinkedNintendoAccountId(OUT nn::account::NintendoAccountId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IGuestLoginRequest::GetNickname(OUT int8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::baas::IGuestLoginRequest::GetProfileImage(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::baas::IGuestLoginRequest::GetSessionId(OUT nn::account::detail::Uuid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IGuestLoginRequest::LoadIdTokenCache(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::baas::IManagerForApplication::CheckAvailability() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IManagerForApplication::CreateAuthorizationRequest(IN uint32_t _0, IN KObject * _1, IN nn::account::NintendoAccountAuthorizationRequestParameters * _2, guint _2_size, OUT nn::account::nas::IAuthorizationRequest * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_3 OMG = new nn::account::nas::IAuthorizationRequest(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IManagerForApplication::EnsureIdTokenCacheAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IManagerForApplication::GetAccountId(OUT nn::account::NetworkServiceAccountId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IManagerForApplication::GetNintendoAccountUserResourceCacheForApplication(OUT nn::account::NintendoAccountId& _0, OUT nn::account::nas::NasUserBaseForApplication * _1, guint _1_size, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::account::baas::IManagerForApplication::LoadIdTokenCache(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::baas::IManagerForSystemService::CheckAvailability() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IManagerForSystemService::CreateAuthorizationRequest(IN uint32_t _0, IN KObject * _1, IN nn::account::nas::NasClientInfo * _2, guint _2_size, IN nn::account::NintendoAccountAuthorizationRequestParameters * _3, guint _3_size, OUT nn::account::nas::IAuthorizationRequest * _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	_4 OMG = new nn::account::nas::IAuthorizationRequest(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IManagerForSystemService::EnsureIdTokenCacheAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IManagerForSystemService::GetAccountId(OUT nn::account::NetworkServiceAccountId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IManagerForSystemService::GetNintendoAccountId(OUT nn::account::NintendoAccountId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::baas::IManagerForSystemService::GetNintendoAccountUserResourceCache(OUT nn::account::NintendoAccountId& _0, OUT nn::account::nas::NasUserBase * _1, guint _1_size, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::account::baas::IManagerForSystemService::LoadIdTokenCache(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::baas::IManagerForSystemService::RefreshNintendoAccountUserResourceCacheAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IManagerForSystemService::RefreshNintendoAccountUserResourceCacheAsyncIfSecondsElapsed(IN uint32_t _0, OUT bool& _1, OUT nn::account::detail::IAsyncContext * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::baas::IManagerForSystemService::SetSystemProgramIdentification(IN uint64_t _0, IN gpid _1, IN nn::account::SystemProgramIdentification * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::account::detail {
	class IAsyncContext {
	public:
		IAsyncContext();
		uint32_t Cancel();
		uint32_t GetResult();
		uint32_t GetSystemEvent(OUT KObject * _0);
		uint32_t HasDone(OUT bool& _0);
	};
	class INotifier {
	public:
		INotifier();
		uint32_t GetSystemEvent(OUT KObject * _0);
	};
	class ISessionObject {
	public:
		ISessionObject();
		uint32_t Dummy();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::account::detail::IAsyncContext::Cancel() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::detail::IAsyncContext::GetResult() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::detail::IAsyncContext::GetSystemEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::account::detail::IAsyncContext::HasDone(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::detail::INotifier::GetSystemEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::account::detail::ISessionObject::Dummy() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::account::http {
	class IOAuthProcedure {
	public:
		IOAuthProcedure();
		uint32_t ApplyResponse(IN int8_t * _0, guint _0_size);
		uint32_t ApplyResponseAsync(IN int8_t * _0, guint _0_size, OUT nn::account::detail::IAsyncContext * _1);
		uint32_t GetRequest(OUT nn::account::RequestUrl * _0, guint _0_size, OUT nn::account::CallbackUri * _1, guint _1_size);
		uint32_t PrepareAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t Suspend(OUT nn::account::detail::Uuid& _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::account::http::IOAuthProcedure::ApplyResponse(IN int8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::http::IOAuthProcedure::ApplyResponseAsync(IN int8_t * _0, guint _0_size, OUT nn::account::detail::IAsyncContext * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_1 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::http::IOAuthProcedure::GetRequest(OUT nn::account::RequestUrl * _0, guint _0_size, OUT nn::account::CallbackUri * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x1a, 1, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::account::http::IOAuthProcedure::PrepareAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::http::IOAuthProcedure::Suspend(OUT nn::account::detail::Uuid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::account::nas {
	class IAuthorizationRequest {
	public:
		IAuthorizationRequest();
		uint32_t GetAuthorizationCode(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetIdToken(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetSessionId(OUT nn::account::detail::Uuid& _0);
		uint32_t GetState(OUT nn::account::nas::State * _0, guint _0_size);
		uint32_t InvokeWithoutInteractionAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t IsAuthorized(OUT bool& _0);
	};
	class IOAuthProcedureForExternalNsa {
	public:
		IOAuthProcedureForExternalNsa();
		uint32_t ApplyResponse(IN int8_t * _0, guint _0_size);
		uint32_t ApplyResponseAsync(IN int8_t * _0, guint _0_size, OUT nn::account::detail::IAsyncContext * _1);
		uint32_t GetAccountId(OUT nn::account::NetworkServiceAccountId& _0);
		uint32_t GetLinkedNintendoAccountId(OUT nn::account::NintendoAccountId& _0);
		uint32_t GetNickname(OUT int8_t * _0, guint _0_size);
		uint32_t GetProfileImage(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetRequest(OUT nn::account::RequestUrl * _0, guint _0_size, OUT nn::account::CallbackUri * _1, guint _1_size);
		uint32_t PrepareAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t Suspend(OUT nn::account::detail::Uuid& _0);
	};
	class IOAuthProcedureForNintendoAccountLinkage {
	public:
		IOAuthProcedureForNintendoAccountLinkage();
		uint32_t ApplyResponse(IN int8_t * _0, guint _0_size);
		uint32_t ApplyResponseAsync(IN int8_t * _0, guint _0_size, OUT nn::account::detail::IAsyncContext * _1);
		uint32_t GetRequest(OUT nn::account::RequestUrl * _0, guint _0_size, OUT nn::account::CallbackUri * _1, guint _1_size);
		uint32_t GetRequestWithTheme(IN int32_t _0, OUT nn::account::RequestUrl * _1, guint _1_size, OUT nn::account::CallbackUri * _2, guint _2_size);
		uint32_t GetUrlForIntroductionOfExtraMembership(OUT nn::account::RequestUrl * _0, guint _0_size);
		uint32_t IsNetworkServiceAccountReplaced(OUT bool& _0);
		uint32_t PrepareAsync(OUT nn::account::detail::IAsyncContext * _0);
		uint32_t Suspend(OUT nn::account::detail::Uuid& _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::account::nas::IAuthorizationRequest::GetAuthorizationCode(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::nas::IAuthorizationRequest::GetIdToken(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::nas::IAuthorizationRequest::GetSessionId(OUT nn::account::detail::Uuid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::nas::IAuthorizationRequest::GetState(OUT nn::account::nas::State * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::nas::IAuthorizationRequest::InvokeWithoutInteractionAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::nas::IAuthorizationRequest::IsAuthorized(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForExternalNsa::ApplyResponse(IN int8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForExternalNsa::ApplyResponseAsync(IN int8_t * _0, guint _0_size, OUT nn::account::detail::IAsyncContext * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_1 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForExternalNsa::GetAccountId(OUT nn::account::NetworkServiceAccountId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForExternalNsa::GetLinkedNintendoAccountId(OUT nn::account::NintendoAccountId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForExternalNsa::GetNickname(OUT int8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForExternalNsa::GetProfileImage(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForExternalNsa::GetRequest(OUT nn::account::RequestUrl * _0, guint _0_size, OUT nn::account::CallbackUri * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x1a, 1, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForExternalNsa::PrepareAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForExternalNsa::Suspend(OUT nn::account::detail::Uuid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForNintendoAccountLinkage::ApplyResponse(IN int8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForNintendoAccountLinkage::ApplyResponseAsync(IN int8_t * _0, guint _0_size, OUT nn::account::detail::IAsyncContext * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_1 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForNintendoAccountLinkage::GetRequest(OUT nn::account::RequestUrl * _0, guint _0_size, OUT nn::account::CallbackUri * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x1a, 1, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForNintendoAccountLinkage::GetRequestWithTheme(IN int32_t _0, OUT nn::account::RequestUrl * _1, guint _1_size, OUT nn::account::CallbackUri * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x1a, 1, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForNintendoAccountLinkage::GetUrlForIntroductionOfExtraMembership(OUT nn::account::RequestUrl * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForNintendoAccountLinkage::IsNetworkServiceAccountReplaced(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForNintendoAccountLinkage::PrepareAsync(OUT nn::account::detail::IAsyncContext * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::account::detail::IAsyncContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::account::nas::IOAuthProcedureForNintendoAccountLinkage::Suspend(OUT nn::account::detail::Uuid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::account::profile {
	class IProfile {
	public:
		IProfile();
		uint32_t Get(OUT nn::account::profile::ProfileBase& _0, OUT nn::account::profile::UserData * _1, guint _1_size);
		uint32_t GetBase(OUT nn::account::profile::ProfileBase& _0);
		uint32_t GetImageSize(OUT uint32_t& _0);
		uint32_t LoadImage(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
	};
	class IProfileEditor {
	public:
		IProfileEditor();
		uint32_t Get(OUT nn::account::profile::ProfileBase& _0, OUT nn::account::profile::UserData * _1, guint _1_size);
		uint32_t GetBase(OUT nn::account::profile::ProfileBase& _0);
		uint32_t GetImageSize(OUT uint32_t& _0);
		uint32_t LoadImage(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Store(IN nn::account::profile::ProfileBase _0, IN nn::account::profile::UserData * _1, guint _1_size);
		uint32_t StoreWithImage(IN nn::account::profile::ProfileBase _0, IN nn::account::profile::UserData * _1, guint _1_size, IN uint8_t * _2, guint _2_size);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::account::profile::IProfile::Get(OUT nn::account::profile::ProfileBase& _0, OUT nn::account::profile::UserData * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::account::profile::ProfileBase>(8);
	guint temp3;
	auto temp2 = req.getBuffer(0x1a, 0, temp3);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp2, temp4, temp3);
	delete[] temp4;
	return ret;
}
uint32_t nn::account::profile::IProfile::GetBase(OUT nn::account::profile::ProfileBase& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::account::profile::ProfileBase>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::profile::IProfile::GetImageSize(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::profile::IProfile::LoadImage(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::profile::IProfileEditor::Get(OUT nn::account::profile::ProfileBase& _0, OUT nn::account::profile::UserData * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::account::profile::ProfileBase>(8);
	guint temp3;
	auto temp2 = req.getBuffer(0x1a, 0, temp3);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp2, temp4, temp3);
	delete[] temp4;
	return ret;
}
uint32_t nn::account::profile::IProfileEditor::GetBase(OUT nn::account::profile::ProfileBase& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::account::profile::ProfileBase>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::profile::IProfileEditor::GetImageSize(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::account::profile::IProfileEditor::LoadImage(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::profile::IProfileEditor::Store(IN nn::account::profile::ProfileBase _0, IN nn::account::profile::UserData * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::account::profile::IProfileEditor::StoreWithImage(IN nn::account::profile::ProfileBase _0, IN nn::account::profile::UserData * _1, guint _1_size, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(5, 0, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::ahid {
	class ICtrlSession {
	public:
		ICtrlSession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
	class IReadSession {
	public:
		IReadSession();
		uint32_t Unknown0();
	};
	class IServerSession {
	public:
		IServerSession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::ahid::ICtrlSession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::ICtrlSession::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::IReadSession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::IServerSession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::IServerSession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::IServerSession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::IServerSession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::ahid::hdr {
	class ISession {
	public:
		ISession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::ahid::hdr::ISession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::hdr::ISession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::hdr::ISession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::hdr::ISession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ahid::hdr::ISession::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::am::service {
	class IAllSystemAppletProxiesService {
	public:
		IAllSystemAppletProxiesService();
		uint32_t CreateSelfLibraryAppletCreatorForDevelop(IN uint64_t _0, IN gpid _1, OUT nn::am::service::ILibraryAppletCreator * _2);
		uint32_t OpenLibraryAppletProxy(IN uint64_t _0, IN gpid _1, IN KObject * _2, IN nn::am::AppletAttribute * _3, guint _3_size, OUT nn::am::service::ILibraryAppletProxy * _4);
		uint32_t OpenLibraryAppletProxyOld(IN uint64_t _0, IN gpid _1, IN KObject * _2, OUT nn::am::service::ILibraryAppletProxy * _3);
		uint32_t OpenOverlayAppletProxy(IN uint64_t _0, IN gpid _1, IN KObject * _2, OUT nn::am::service::IOverlayAppletProxy * _3);
		uint32_t OpenSystemAppletProxy(IN uint64_t _0, IN gpid _1, IN KObject * _2, OUT nn::am::service::ISystemAppletProxy * _3);
		uint32_t OpenSystemApplicationProxy(IN uint64_t _0, IN gpid _1, IN KObject * _2, OUT nn::am::service::IApplicationProxy * _3);
	};
	class IAppletAccessor {
	public:
		IAppletAccessor();
		uint32_t GetAppletStateChangedEvent(OUT KObject * _0);
		uint32_t GetResult();
		uint32_t IsCompleted(OUT bool& _0);
		uint32_t RequestExit();
		uint32_t Start();
		uint32_t Terminate();
	};
	class IApplicationAccessor {
	public:
		IApplicationAccessor();
		uint32_t AreAnyLibraryAppletsLeft(OUT bool& _0);
		uint32_t GetAppletStateChangedEvent(OUT KObject * _0);
		uint32_t GetApplicationControlProperty(OUT uint8_t * _0, guint _0_size);
		uint32_t GetApplicationId(OUT nn::ncm::ApplicationId& _0);
		uint32_t GetApplicationLaunchProperty(OUT uint8_t * _0, guint _0_size);
		uint32_t GetCurrentLibraryApplet(OUT nn::am::service::IAppletAccessor * _0);
		uint32_t GetResult();
		uint32_t IsCompleted(OUT bool& _0);
		uint32_t PushLaunchParameter(IN uint32_t _0, IN nn::am::service::IStorage * _1);
		uint32_t RequestExit();
		uint32_t RequestForApplicationToGetForeground();
		uint32_t Start();
		uint32_t Terminate();
		uint32_t TerminateAllLibraryApplets();
	};
	class IApplicationCreator {
	public:
		IApplicationCreator();
		uint32_t CreateApplication(IN nn::ncm::ApplicationId _0, OUT nn::am::service::IApplicationAccessor * _1);
		uint32_t CreateSystemApplication(IN nn::ncm::SystemApplicationId _0, OUT nn::am::service::IApplicationAccessor * _1);
		uint32_t PopFloatingApplicationForDevelopment(OUT nn::am::service::IApplicationAccessor * _0);
		uint32_t PopLaunchRequestedApplication(OUT nn::am::service::IApplicationAccessor * _0);
	};
	class IApplicationFunctions {
	public:
		IApplicationFunctions();
		uint32_t BeginBlockingHomeButton(IN int64_t _0);
		uint32_t BeginBlockingHomeButtonShortAndLongPressed(IN int64_t _0);
		uint32_t CreateApplicationAndPushAndRequestToStart(IN nn::ncm::ApplicationId _0, IN nn::am::service::IStorage * _1);
		uint32_t CreateApplicationAndPushAndRequestToStartForQuest(IN uint32_t _0, IN uint32_t _1, IN nn::ncm::ApplicationId _2, IN nn::am::service::IStorage * _3);
		uint32_t EndBlockingHomeButton();
		uint32_t EndBlockingHomeButtonShortAndLongPressed();
		uint32_t EnsureSaveData(IN nn::account::Uid _0, OUT int64_t& _1);
		uint32_t ExtendSaveData(IN uint8_t _0, IN nn::account::Uid _1, IN int64_t _2, IN int64_t _3, OUT int64_t& _4);
		uint32_t GetDesiredLanguage(OUT nn::settings::LanguageCode& _0);
		uint32_t GetDisplayVersion(OUT nn::oe::DisplayVersion& _0);
		uint32_t GetLaunchStorageInfoForDebug(OUT nn::ncm::StorageId& _0, OUT nn::ncm::StorageId& _1);
		uint32_t GetPseudoDeviceId(OUT nn::util::Uuid& _0);
		uint32_t GetSaveDataSize(IN uint8_t _0, IN nn::account::Uid _1, OUT int64_t& _2, OUT int64_t& _3);
		uint32_t InitializeGamePlayRecording(IN uint64_t _0, IN KObject * _1);
		uint32_t IsGamePlayRecordingSupported(OUT bool& _0);
		uint32_t NotifyRunning(OUT bool& _0);
		uint32_t PopLaunchParameter(IN uint32_t _0, OUT nn::am::service::IStorage * _1);
		uint32_t RequestToReboot();
		uint32_t RequestToShutdown();
		uint32_t SetGamePlayRecordingState(IN int32_t _0);
		uint32_t SetMediaPlaybackStateForApplication(IN bool _0);
		uint32_t SetTerminateResult(IN uint32_t _0);
	};
	class IApplicationProxy {
	public:
		IApplicationProxy();
		uint32_t GetApplicationFunctions(OUT nn::am::service::IApplicationFunctions * _0);
		uint32_t GetAudioController(OUT nn::am::service::IAudioController * _0);
		uint32_t GetCommonStateGetter(OUT nn::am::service::ICommonStateGetter * _0);
		uint32_t GetDebugFunctions(OUT nn::am::service::IDebugFunctions * _0);
		uint32_t GetDisplayController(OUT nn::am::service::IDisplayController * _0);
		uint32_t GetLibraryAppletCreator(OUT nn::am::service::ILibraryAppletCreator * _0);
		uint32_t GetProcessWindingController(OUT nn::am::service::IProcessWindingController * _0);
		uint32_t GetSelfController(OUT nn::am::service::ISelfController * _0);
		uint32_t GetWindowController(OUT nn::am::service::IWindowController * _0);
	};
	class IApplicationProxyService {
	public:
		IApplicationProxyService();
		uint32_t OpenApplicationProxy(IN uint64_t _0, IN gpid _1, IN KObject * _2, OUT nn::am::service::IApplicationProxy * _3);
	};
	class IAudioController {
	public:
		IAudioController();
		uint32_t ChangeMainAppletMasterVolume(IN float32_t _0, IN int64_t _1);
		uint32_t GetLibraryAppletExpectedMasterVolume(OUT float32_t& _0);
		uint32_t GetMainAppletExpectedMasterVolume(OUT float32_t& _0);
		uint32_t SetExpectedMasterVolume(IN float32_t _0, IN float32_t _1);
		uint32_t SetTransparentVolumeRate(IN float32_t _0);
	};
	class ICommonStateGetter {
	public:
		ICommonStateGetter();
		uint32_t AllowToEnterSleep();
		uint32_t DisallowToEnterSleep();
		uint32_t GetAcquiredSleepLockEvent(OUT KObject * _0);
		uint32_t GetBootMode(OUT uint8_t& _0);
		uint32_t GetCradleFwVersion(OUT uint32_t& _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t GetCradleStatus(OUT uint8_t& _0);
		uint32_t GetCurrentFocusState(OUT uint8_t& _0);
		uint32_t GetDefaultDisplayResolution(OUT int32_t& _0, OUT int32_t& _1);
		uint32_t GetDefaultDisplayResolutionChangeEvent(OUT KObject * _0);
		uint32_t GetEventHandle(OUT KObject * _0);
		uint32_t GetHomeButtonReaderLockAccessor(OUT nn::am::service::ILockAccessor * _0);
		uint32_t GetOperationMode(OUT uint8_t& _0);
		uint32_t GetPerformanceMode(OUT uint32_t& _0);
		uint32_t GetReaderLockAccessorEx(IN int32_t _0, OUT nn::am::service::ILockAccessor * _1);
		uint32_t GetThisAppletKind(OUT nn::am::service::AppletKind& _0);
		uint32_t IsInControllerFirmwareUpdateSection(OUT bool& _0);
		uint32_t IsVrModeEnabled(OUT bool& _0);
		uint32_t PushToGeneralChannel(IN nn::am::service::IStorage * _0);
		uint32_t ReceiveMessage(OUT nn::am::AppletMessage& _0);
		uint32_t ReleaseSleepLock();
		uint32_t ReleaseSleepLockTransiently();
		uint32_t RequestToAcquireSleepLock();
		uint32_t SetVrModeEnabled(IN bool _0);
	};
	class IDebugFunctions {
	public:
		IDebugFunctions();
		uint32_t EmulateButtonEvent(IN nn::am::service::EmulatedButtonEvent _0);
		uint32_t InvalidateTransitionLayer();
		uint32_t NotifyMessageToHomeMenuForDebug(IN nn::am::AppletMessage _0);
		uint32_t OpenMainApplication(OUT nn::am::service::IApplicationAccessor * _0);
	};
	class IDisplayController {
	public:
		IDisplayController();
		uint32_t AcquireCallerAppletCaptureBuffer(OUT KObject * _0);
		uint32_t AcquireCallerAppletCaptureBufferEx(OUT bool& _0, OUT KObject * _1);
		uint32_t AcquireLastApplicationCaptureBuffer(OUT KObject * _0);
		uint32_t AcquireLastApplicationCaptureBufferEx(OUT bool& _0, OUT KObject * _1);
		uint32_t AcquireLastForegroundCaptureBuffer(OUT KObject * _0);
		uint32_t AcquireLastForegroundCaptureBufferEx(OUT bool& _0, OUT KObject * _1);
		uint32_t ClearAppletTransitionBuffer(IN uint32_t _0);
		uint32_t ClearCaptureBuffer(IN bool _0, IN int32_t _1, IN uint32_t _2);
		uint32_t GetCallerAppletCaptureImage(OUT uint8_t * _0, guint _0_size);
		uint32_t GetCallerAppletCaptureImageEx(OUT bool& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetLastApplicationCaptureImage(OUT uint8_t * _0, guint _0_size);
		uint32_t GetLastApplicationCaptureImageEx(OUT bool& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetLastForegroundCaptureImage(OUT uint8_t * _0, guint _0_size);
		uint32_t GetLastForegroundCaptureImageEx(OUT bool& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t ReleaseCallerAppletCaptureBuffer();
		uint32_t ReleaseLastApplicationCaptureBuffer();
		uint32_t ReleaseLastForegroundCaptureBuffer();
		uint32_t TakeScreenShotOfOwnLayer(IN bool _0, IN int32_t _1);
		uint32_t UpdateCallerAppletCaptureImage();
		uint32_t UpdateLastForegroundCaptureImage();
	};
	class IGlobalStateController {
	public:
		IGlobalStateController();
		uint32_t EnterSleep();
		uint32_t LoadAndApplyIdlePolicySettings();
		uint32_t NotifyCecSettingsChanged();
		uint32_t RequestToEnterSleep();
		uint32_t SetDefaultHomeButtonLongPressTime(IN int64_t _0);
		uint32_t ShouldSleepOnBoot(OUT bool& _0);
		uint32_t StartRebootSequence();
		uint32_t StartShutdownSequence();
		uint32_t StartSleepSequence(IN bool _0);
		uint32_t UpdateDefaultDisplayResolution();
	};
	class IHomeMenuFunctions {
	public:
		IHomeMenuFunctions();
		uint32_t GetHomeButtonWriterLockAccessor(OUT nn::am::service::ILockAccessor * _0);
		uint32_t GetPopFromGeneralChannelEvent(OUT KObject * _0);
		uint32_t GetWriterLockAccessorEx(IN int32_t _0, OUT nn::am::service::ILockAccessor * _1);
		uint32_t LockForeground();
		uint32_t PopFromGeneralChannel(OUT nn::am::service::IStorage * _0);
		uint32_t RequestToGetForeground();
		uint32_t UnlockForeground();
	};
	class ILibraryAppletAccessor {
	public:
		ILibraryAppletAccessor();
		uint32_t GetAppletStateChangedEvent(OUT KObject * _0);
		uint32_t GetIndirectLayerConsumerHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT uint64_t& _2);
		uint32_t GetLibraryAppletInfo(OUT nn::am::service::LibraryAppletInfo& _0);
		uint32_t GetPopInteractiveOutDataEvent(OUT KObject * _0);
		uint32_t GetPopOutDataEvent(OUT KObject * _0);
		uint32_t GetResult();
		uint32_t IsCompleted(OUT bool& _0);
		uint32_t NeedsToExitProcess(OUT bool& _0);
		uint32_t PopInteractiveOutData(OUT nn::am::service::IStorage * _0);
		uint32_t PopOutData(OUT nn::am::service::IStorage * _0);
		uint32_t PushExtraStorage(IN nn::am::service::IStorage * _0);
		uint32_t PushInData(IN nn::am::service::IStorage * _0);
		uint32_t PushInteractiveInData(IN nn::am::service::IStorage * _0);
		uint32_t RequestExit();
		uint32_t RequestForAppletToGetForeground();
		uint32_t SetOutOfFocusApplicationSuspendingEnabled(IN bool _0);
		uint32_t Start();
		uint32_t Terminate();
	};
	class ILibraryAppletCreator {
	public:
		ILibraryAppletCreator();
		uint32_t AreAnyLibraryAppletsLeft(OUT bool& _0);
		uint32_t CreateHandleStorage(IN int64_t _0, IN KObject * _1, OUT nn::am::service::IStorage * _2);
		uint32_t CreateLibraryApplet(IN uint32_t _0, IN uint32_t _1, OUT nn::am::service::ILibraryAppletAccessor * _2);
		uint32_t CreateStorage(IN int64_t _0, OUT nn::am::service::IStorage * _1);
		uint32_t CreateTransferMemoryStorage(IN bool _0, IN int64_t _1, IN KObject * _2, OUT nn::am::service::IStorage * _3);
		uint32_t TerminateAllLibraryApplets();
	};
	class ILibraryAppletProxy {
	public:
		ILibraryAppletProxy();
		uint32_t GetAudioController(OUT nn::am::service::IAudioController * _0);
		uint32_t GetCommonStateGetter(OUT nn::am::service::ICommonStateGetter * _0);
		uint32_t GetDebugFunctions(OUT nn::am::service::IDebugFunctions * _0);
		uint32_t GetDisplayController(OUT nn::am::service::IDisplayController * _0);
		uint32_t GetLibraryAppletCreator(OUT nn::am::service::ILibraryAppletCreator * _0);
		uint32_t GetProcessWindingController(OUT nn::am::service::IProcessWindingController * _0);
		uint32_t GetSelfController(OUT nn::am::service::ISelfController * _0);
		uint32_t GetWindowController(OUT nn::am::service::IWindowController * _0);
		uint32_t OpenLibraryAppletSelfAccessor(OUT nn::am::service::ILibraryAppletSelfAccessor * _0);
	};
	class ILibraryAppletSelfAccessor {
	public:
		ILibraryAppletSelfAccessor();
		uint32_t CanUseApplicationCore(OUT bool& _0);
		uint32_t ExitProcessAndReturn();
		uint32_t GetCallerAppletIdentityInfo(OUT nn::am::service::AppletIdentityInfo& _0);
		uint32_t GetCallerAppletIdentityInfoStack(OUT int32_t& _0, OUT nn::am::service::AppletIdentityInfo * _1, guint _1_size);
		uint32_t GetIndirectLayerProducerHandle(OUT uint64_t& _0);
		uint32_t GetLibraryAppletInfo(OUT nn::am::service::LibraryAppletInfo& _0);
		uint32_t GetMainAppletApplicationControlProperty(OUT nn::ns::ApplicationControlProperty * _0, guint _0_size);
		uint32_t GetMainAppletIdentityInfo(OUT nn::am::service::AppletIdentityInfo& _0);
		uint32_t GetMainAppletStorageId(OUT nn::ncm::StorageId& _0);
		uint32_t GetPopExtraStorageEvent(OUT KObject * _0);
		uint32_t GetPopInDataEvent(OUT KObject * _0);
		uint32_t GetPopInteractiveInDataEvent(OUT KObject * _0);
		uint32_t PopExtraStorage(OUT nn::am::service::IStorage * _0);
		uint32_t PopInData(OUT nn::am::service::IStorage * _0);
		uint32_t PopInteractiveInData(OUT nn::am::service::IStorage * _0);
		uint32_t PushInteractiveOutData(IN nn::am::service::IStorage * _0);
		uint32_t PushOutData(IN nn::am::service::IStorage * _0);
		uint32_t ReportVisibleError(IN nn::err::ErrorCode _0);
		uint32_t UnpopExtraStorage(IN nn::am::service::IStorage * _0);
		uint32_t UnpopInData(IN nn::am::service::IStorage * _0);
	};
	class ILockAccessor {
	public:
		ILockAccessor();
		uint32_t GetEvent(OUT KObject * _0);
		uint32_t TryLock(IN bool _0, OUT bool& _1, OUT KObject * _2);
		uint32_t Unlock();
	};
	class IOverlayAppletProxy {
	public:
		IOverlayAppletProxy();
		uint32_t GetAudioController(OUT nn::am::service::IAudioController * _0);
		uint32_t GetCommonStateGetter(OUT nn::am::service::ICommonStateGetter * _0);
		uint32_t GetDebugFunctions(OUT nn::am::service::IDebugFunctions * _0);
		uint32_t GetDisplayController(OUT nn::am::service::IDisplayController * _0);
		uint32_t GetLibraryAppletCreator(OUT nn::am::service::ILibraryAppletCreator * _0);
		uint32_t GetOverlayFunctions(OUT nn::am::service::IOverlayFunctions * _0);
		uint32_t GetProcessWindingController(OUT nn::am::service::IProcessWindingController * _0);
		uint32_t GetSelfController(OUT nn::am::service::ISelfController * _0);
		uint32_t GetWindowController(OUT nn::am::service::IWindowController * _0);
	};
	class IOverlayFunctions {
	public:
		IOverlayFunctions();
		uint32_t BeginToWatchShortHomeButtonMessage();
		uint32_t EndToWatchShortHomeButtonMessage();
		uint32_t GetApplicationIdForLogo(OUT nn::ncm::ApplicationId& _0);
		uint32_t SetAutoSleepTimeAndDimmingTimeEnabled(IN bool _0);
		uint32_t SetGpuTimeSliceBoost(IN uint64_t _0);
		uint32_t SetScreenShotPermissionGlobally(IN bool _0);
		uint32_t TerminateApplicationAndSetReason(IN uint32_t _0);
	};
	class IProcessWindingController {
	public:
		IProcessWindingController();
		uint32_t CancelWindingReservation();
		uint32_t GetLaunchReason(OUT nn::am::service::AppletProcessLaunchReason& _0);
		uint32_t OpenCallingLibraryApplet(OUT nn::am::service::ILibraryAppletAccessor * _0);
		uint32_t PopContext(OUT nn::am::service::IStorage * _0);
		uint32_t PushContext(IN nn::am::service::IStorage * _0);
		uint32_t ReserveToStartAndWaitAndUnwindThis(IN nn::am::service::ILibraryAppletAccessor * _0);
		uint32_t WindAndDoReserved();
	};
	class ISelfController {
	public:
		ISelfController();
		uint32_t ApproveToDisplay();
		uint32_t CreateManagedDisplayLayer(OUT uint64_t& _0);
		uint32_t EnterFatalSection();
		uint32_t Exit();
		uint32_t GetCurrentIlluminance(OUT float32_t& _0);
		uint32_t GetIdleTimeDetectionExtension(OUT uint32_t& _0);
		uint32_t GetLibraryAppletLaunchableEvent(OUT KObject * _0);
		uint32_t IsIlluminanceAvailable(OUT bool& _0);
		uint32_t LeaveFatalSection();
		uint32_t LockExit();
		uint32_t OverrideAutoSleepTimeAndDimmingTime(IN int32_t _0, IN int32_t _1, IN int32_t _2, IN int32_t _3);
		uint32_t ReportUserIsActive();
		uint32_t SetControllerFirmwareUpdateSection(IN bool _0);
		uint32_t SetFocusHandlingMode(IN bool _0, IN bool _1, IN bool _2);
		uint32_t SetHandlesRequestToDisplay(IN bool _0);
		uint32_t SetIdleTimeDetectionExtension(IN uint32_t _0);
		uint32_t SetInputDetectionSourceSet(IN uint32_t _0);
		uint32_t SetMediaPlaybackState(IN bool _0);
		uint32_t SetOperationModeChangedNotification(IN bool _0);
		uint32_t SetOutOfFocusSuspendingEnabled(IN bool _0);
		uint32_t SetPerformanceModeChangedNotification(IN bool _0);
		uint32_t SetRequiresCaptureButtonShortPressedMessage(IN bool _0);
		uint32_t SetRestartMessageEnabled(IN bool _0);
		uint32_t SetScreenShotAppletIdentityInfo(IN nn::am::service::AppletIdentityInfo _0);
		uint32_t SetScreenShotImageOrientation(IN int32_t _0);
		uint32_t SetScreenShotPermission(IN int32_t _0);
		uint32_t UnlockExit();
	};
	class IStorage {
	public:
		IStorage();
		uint32_t Open(OUT nn::am::service::IStorageAccessor * _0);
		uint32_t OpenTransferStorage(OUT nn::am::service::ITransferStorageAccessor * _0);
	};
	class IStorageAccessor {
	public:
		IStorageAccessor();
		uint32_t GetSize(OUT int64_t& _0);
		uint32_t Read(IN int64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Write(IN int64_t _0, IN uint8_t * _1, guint _1_size);
	};
	class ISystemAppletProxy {
	public:
		ISystemAppletProxy();
		uint32_t GetApplicationCreator(OUT nn::am::service::IApplicationCreator * _0);
		uint32_t GetAudioController(OUT nn::am::service::IAudioController * _0);
		uint32_t GetCommonStateGetter(OUT nn::am::service::ICommonStateGetter * _0);
		uint32_t GetDebugFunctions(OUT nn::am::service::IDebugFunctions * _0);
		uint32_t GetDisplayController(OUT nn::am::service::IDisplayController * _0);
		uint32_t GetGlobalStateController(OUT nn::am::service::IGlobalStateController * _0);
		uint32_t GetHomeMenuFunctions(OUT nn::am::service::IHomeMenuFunctions * _0);
		uint32_t GetLibraryAppletCreator(OUT nn::am::service::ILibraryAppletCreator * _0);
		uint32_t GetProcessWindingController(OUT nn::am::service::IProcessWindingController * _0);
		uint32_t GetSelfController(OUT nn::am::service::ISelfController * _0);
		uint32_t GetWindowController(OUT nn::am::service::IWindowController * _0);
	};
	class ITransferStorageAccessor {
	public:
		ITransferStorageAccessor();
		uint32_t GetHandle(OUT uint64_t& _0, OUT KObject * _1);
		uint32_t GetSize(OUT int64_t& _0);
	};
	class IWindow {
	public:
		IWindow();
		uint32_t Unknown12345();
	};
	class IWindowController {
	public:
		IWindowController();
		uint32_t AcquireForegroundRights();
		uint32_t CreateWindow(IN nn::am::service::WindowCreationOption _0, OUT nn::am::service::IWindow * _1);
		uint32_t GetAppletResourceUserId(OUT nn::applet::AppletResourceUserId& _0);
		uint32_t RejectToChangeIntoBackground();
		uint32_t ReleaseForegroundRights();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::am::service::IAllSystemAppletProxiesService::CreateSelfLibraryAppletCreatorForDevelop(IN uint64_t _0, IN gpid _1, OUT nn::am::service::ILibraryAppletCreator * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::am::service::ILibraryAppletCreator(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IAllSystemAppletProxiesService::OpenLibraryAppletProxy(IN uint64_t _0, IN gpid _1, IN KObject * _2, IN nn::am::AppletAttribute * _3, guint _3_size, OUT nn::am::service::ILibraryAppletProxy * _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x15, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_4 OMG = new nn::am::service::ILibraryAppletProxy(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IAllSystemAppletProxiesService::OpenLibraryAppletProxyOld(IN uint64_t _0, IN gpid _1, IN KObject * _2, OUT nn::am::service::ILibraryAppletProxy * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_3 OMG = new nn::am::service::ILibraryAppletProxy(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IAllSystemAppletProxiesService::OpenOverlayAppletProxy(IN uint64_t _0, IN gpid _1, IN KObject * _2, OUT nn::am::service::IOverlayAppletProxy * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_3 OMG = new nn::am::service::IOverlayAppletProxy(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IAllSystemAppletProxiesService::OpenSystemAppletProxy(IN uint64_t _0, IN gpid _1, IN KObject * _2, OUT nn::am::service::ISystemAppletProxy * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_3 OMG = new nn::am::service::ISystemAppletProxy(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IAllSystemAppletProxiesService::OpenSystemApplicationProxy(IN uint64_t _0, IN gpid _1, IN KObject * _2, OUT nn::am::service::IApplicationProxy * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_3 OMG = new nn::am::service::IApplicationProxy(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IAppletAccessor::GetAppletStateChangedEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::IAppletAccessor::GetResult() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IAppletAccessor::IsCompleted(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IAppletAccessor::RequestExit() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IAppletAccessor::Start() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IAppletAccessor::Terminate() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::AreAnyLibraryAppletsLeft(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::GetAppletStateChangedEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::GetApplicationControlProperty(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::GetApplicationId(OUT nn::ncm::ApplicationId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::GetApplicationLaunchProperty(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::GetCurrentLibraryApplet(OUT nn::am::service::IAppletAccessor * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IAppletAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::GetResult() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::IsCompleted(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::PushLaunchParameter(IN uint32_t _0, IN nn::am::service::IStorage * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::RequestExit() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::RequestForApplicationToGetForeground() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::Start() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::Terminate() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationAccessor::TerminateAllLibraryApplets() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationCreator::CreateApplication(IN nn::ncm::ApplicationId _0, OUT nn::am::service::IApplicationAccessor * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::am::service::IApplicationAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationCreator::CreateSystemApplication(IN nn::ncm::SystemApplicationId _0, OUT nn::am::service::IApplicationAccessor * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::am::service::IApplicationAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationCreator::PopFloatingApplicationForDevelopment(OUT nn::am::service::IApplicationAccessor * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IApplicationAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationCreator::PopLaunchRequestedApplication(OUT nn::am::service::IApplicationAccessor * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IApplicationAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::BeginBlockingHomeButton(IN int64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::BeginBlockingHomeButtonShortAndLongPressed(IN int64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::CreateApplicationAndPushAndRequestToStart(IN nn::ncm::ApplicationId _0, IN nn::am::service::IStorage * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::CreateApplicationAndPushAndRequestToStartForQuest(IN uint32_t _0, IN uint32_t _1, IN nn::ncm::ApplicationId _2, IN nn::am::service::IStorage * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::EndBlockingHomeButton() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::EndBlockingHomeButtonShortAndLongPressed() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::EnsureSaveData(IN nn::account::Uid _0, OUT int64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::ExtendSaveData(IN uint8_t _0, IN nn::account::Uid _1, IN int64_t _2, IN int64_t _3, OUT int64_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::GetDesiredLanguage(OUT nn::settings::LanguageCode& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::GetDisplayVersion(OUT nn::oe::DisplayVersion& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::GetLaunchStorageInfoForDebug(OUT nn::ncm::StorageId& _0, OUT nn::ncm::StorageId& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::GetPseudoDeviceId(OUT nn::util::Uuid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::GetSaveDataSize(IN uint8_t _0, IN nn::account::Uid _1, OUT int64_t& _2, OUT int64_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::InitializeGamePlayRecording(IN uint64_t _0, IN KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::IsGamePlayRecordingSupported(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::NotifyRunning(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::PopLaunchParameter(IN uint32_t _0, OUT nn::am::service::IStorage * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::am::service::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::RequestToReboot() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::RequestToShutdown() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::SetGamePlayRecordingState(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::SetMediaPlaybackStateForApplication(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationFunctions::SetTerminateResult(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IApplicationProxy::GetApplicationFunctions(OUT nn::am::service::IApplicationFunctions * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IApplicationFunctions(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationProxy::GetAudioController(OUT nn::am::service::IAudioController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IAudioController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationProxy::GetCommonStateGetter(OUT nn::am::service::ICommonStateGetter * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ICommonStateGetter(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationProxy::GetDebugFunctions(OUT nn::am::service::IDebugFunctions * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IDebugFunctions(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationProxy::GetDisplayController(OUT nn::am::service::IDisplayController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IDisplayController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationProxy::GetLibraryAppletCreator(OUT nn::am::service::ILibraryAppletCreator * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ILibraryAppletCreator(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationProxy::GetProcessWindingController(OUT nn::am::service::IProcessWindingController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IProcessWindingController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationProxy::GetSelfController(OUT nn::am::service::ISelfController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ISelfController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationProxy::GetWindowController(OUT nn::am::service::IWindowController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IWindowController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IApplicationProxyService::OpenApplicationProxy(IN uint64_t _0, IN gpid _1, IN KObject * _2, OUT nn::am::service::IApplicationProxy * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_3 OMG = new nn::am::service::IApplicationProxy(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IAudioController::ChangeMainAppletMasterVolume(IN float32_t _0, IN int64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IAudioController::GetLibraryAppletExpectedMasterVolume(OUT float32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IAudioController::GetMainAppletExpectedMasterVolume(OUT float32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IAudioController::SetExpectedMasterVolume(IN float32_t _0, IN float32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IAudioController::SetTransparentVolumeRate(IN float32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::AllowToEnterSleep() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::DisallowToEnterSleep() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetAcquiredSleepLockEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetBootMode(OUT uint8_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetCradleFwVersion(OUT uint32_t& _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetCradleStatus(OUT uint8_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetCurrentFocusState(OUT uint8_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetDefaultDisplayResolution(OUT int32_t& _0, OUT int32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetDefaultDisplayResolutionChangeEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetEventHandle(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetHomeButtonReaderLockAccessor(OUT nn::am::service::ILockAccessor * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ILockAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetOperationMode(OUT uint8_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetPerformanceMode(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetReaderLockAccessorEx(IN int32_t _0, OUT nn::am::service::ILockAccessor * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::am::service::ILockAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::GetThisAppletKind(OUT nn::am::service::AppletKind& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::IsInControllerFirmwareUpdateSection(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::IsVrModeEnabled(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::PushToGeneralChannel(IN nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::ReceiveMessage(OUT nn::am::AppletMessage& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::ReleaseSleepLock() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::ReleaseSleepLockTransiently() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::RequestToAcquireSleepLock() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ICommonStateGetter::SetVrModeEnabled(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IDebugFunctions::EmulateButtonEvent(IN nn::am::service::EmulatedButtonEvent _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IDebugFunctions::InvalidateTransitionLayer() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IDebugFunctions::NotifyMessageToHomeMenuForDebug(IN nn::am::AppletMessage _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IDebugFunctions::OpenMainApplication(OUT nn::am::service::IApplicationAccessor * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IApplicationAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IDisplayController::AcquireCallerAppletCaptureBuffer(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::IDisplayController::AcquireCallerAppletCaptureBufferEx(OUT bool& _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::IDisplayController::AcquireLastApplicationCaptureBuffer(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::IDisplayController::AcquireLastApplicationCaptureBufferEx(OUT bool& _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::IDisplayController::AcquireLastForegroundCaptureBuffer(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::IDisplayController::AcquireLastForegroundCaptureBufferEx(OUT bool& _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::IDisplayController::ClearAppletTransitionBuffer(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IDisplayController::ClearCaptureBuffer(IN bool _0, IN int32_t _1, IN uint32_t _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IDisplayController::GetCallerAppletCaptureImage(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::IDisplayController::GetCallerAppletCaptureImageEx(OUT bool& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::IDisplayController::GetLastApplicationCaptureImage(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::IDisplayController::GetLastApplicationCaptureImageEx(OUT bool& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::IDisplayController::GetLastForegroundCaptureImage(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::IDisplayController::GetLastForegroundCaptureImageEx(OUT bool& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::IDisplayController::ReleaseCallerAppletCaptureBuffer() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IDisplayController::ReleaseLastApplicationCaptureBuffer() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IDisplayController::ReleaseLastForegroundCaptureBuffer() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IDisplayController::TakeScreenShotOfOwnLayer(IN bool _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IDisplayController::UpdateCallerAppletCaptureImage() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IDisplayController::UpdateLastForegroundCaptureImage() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IGlobalStateController::EnterSleep() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IGlobalStateController::LoadAndApplyIdlePolicySettings() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IGlobalStateController::NotifyCecSettingsChanged() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IGlobalStateController::RequestToEnterSleep() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IGlobalStateController::SetDefaultHomeButtonLongPressTime(IN int64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IGlobalStateController::ShouldSleepOnBoot(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IGlobalStateController::StartRebootSequence() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IGlobalStateController::StartShutdownSequence() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IGlobalStateController::StartSleepSequence(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IGlobalStateController::UpdateDefaultDisplayResolution() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IHomeMenuFunctions::GetHomeButtonWriterLockAccessor(OUT nn::am::service::ILockAccessor * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ILockAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IHomeMenuFunctions::GetPopFromGeneralChannelEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::IHomeMenuFunctions::GetWriterLockAccessorEx(IN int32_t _0, OUT nn::am::service::ILockAccessor * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::am::service::ILockAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IHomeMenuFunctions::LockForeground() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IHomeMenuFunctions::PopFromGeneralChannel(OUT nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IHomeMenuFunctions::RequestToGetForeground() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IHomeMenuFunctions::UnlockForeground() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::GetAppletStateChangedEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::GetIndirectLayerConsumerHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT uint64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::GetLibraryAppletInfo(OUT nn::am::service::LibraryAppletInfo& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::GetPopInteractiveOutDataEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::GetPopOutDataEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::GetResult() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::IsCompleted(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::NeedsToExitProcess(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::PopInteractiveOutData(OUT nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::PopOutData(OUT nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::PushExtraStorage(IN nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::PushInData(IN nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::PushInteractiveInData(IN nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::RequestExit() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::RequestForAppletToGetForeground() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::SetOutOfFocusApplicationSuspendingEnabled(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::Start() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletAccessor::Terminate() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletCreator::AreAnyLibraryAppletsLeft(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletCreator::CreateHandleStorage(IN int64_t _0, IN KObject * _1, OUT nn::am::service::IStorage * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::am::service::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletCreator::CreateLibraryApplet(IN uint32_t _0, IN uint32_t _1, OUT nn::am::service::ILibraryAppletAccessor * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::am::service::ILibraryAppletAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletCreator::CreateStorage(IN int64_t _0, OUT nn::am::service::IStorage * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::am::service::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletCreator::CreateTransferMemoryStorage(IN bool _0, IN int64_t _1, IN KObject * _2, OUT nn::am::service::IStorage * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_3 OMG = new nn::am::service::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletCreator::TerminateAllLibraryApplets() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletProxy::GetAudioController(OUT nn::am::service::IAudioController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IAudioController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletProxy::GetCommonStateGetter(OUT nn::am::service::ICommonStateGetter * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ICommonStateGetter(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletProxy::GetDebugFunctions(OUT nn::am::service::IDebugFunctions * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IDebugFunctions(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletProxy::GetDisplayController(OUT nn::am::service::IDisplayController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IDisplayController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletProxy::GetLibraryAppletCreator(OUT nn::am::service::ILibraryAppletCreator * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ILibraryAppletCreator(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletProxy::GetProcessWindingController(OUT nn::am::service::IProcessWindingController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IProcessWindingController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletProxy::GetSelfController(OUT nn::am::service::ISelfController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ISelfController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletProxy::GetWindowController(OUT nn::am::service::IWindowController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IWindowController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletProxy::OpenLibraryAppletSelfAccessor(OUT nn::am::service::ILibraryAppletSelfAccessor * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ILibraryAppletSelfAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::CanUseApplicationCore(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::ExitProcessAndReturn() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::GetCallerAppletIdentityInfo(OUT nn::am::service::AppletIdentityInfo& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::GetCallerAppletIdentityInfoStack(OUT int32_t& _0, OUT nn::am::service::AppletIdentityInfo * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::GetIndirectLayerProducerHandle(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::GetLibraryAppletInfo(OUT nn::am::service::LibraryAppletInfo& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::GetMainAppletApplicationControlProperty(OUT nn::ns::ApplicationControlProperty * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::GetMainAppletIdentityInfo(OUT nn::am::service::AppletIdentityInfo& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::GetMainAppletStorageId(OUT nn::ncm::StorageId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::GetPopExtraStorageEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::GetPopInDataEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::GetPopInteractiveInDataEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::PopExtraStorage(OUT nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::PopInData(OUT nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::PopInteractiveInData(OUT nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::PushInteractiveOutData(IN nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::PushOutData(IN nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::ReportVisibleError(IN nn::err::ErrorCode _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::UnpopExtraStorage(IN nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILibraryAppletSelfAccessor::UnpopInData(IN nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ILockAccessor::GetEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ILockAccessor::TryLock(IN bool _0, OUT bool& _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ILockAccessor::Unlock() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IOverlayAppletProxy::GetAudioController(OUT nn::am::service::IAudioController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IAudioController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IOverlayAppletProxy::GetCommonStateGetter(OUT nn::am::service::ICommonStateGetter * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ICommonStateGetter(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IOverlayAppletProxy::GetDebugFunctions(OUT nn::am::service::IDebugFunctions * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IDebugFunctions(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IOverlayAppletProxy::GetDisplayController(OUT nn::am::service::IDisplayController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IDisplayController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IOverlayAppletProxy::GetLibraryAppletCreator(OUT nn::am::service::ILibraryAppletCreator * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ILibraryAppletCreator(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IOverlayAppletProxy::GetOverlayFunctions(OUT nn::am::service::IOverlayFunctions * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IOverlayFunctions(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IOverlayAppletProxy::GetProcessWindingController(OUT nn::am::service::IProcessWindingController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IProcessWindingController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IOverlayAppletProxy::GetSelfController(OUT nn::am::service::ISelfController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ISelfController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IOverlayAppletProxy::GetWindowController(OUT nn::am::service::IWindowController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IWindowController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IOverlayFunctions::BeginToWatchShortHomeButtonMessage() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IOverlayFunctions::EndToWatchShortHomeButtonMessage() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IOverlayFunctions::GetApplicationIdForLogo(OUT nn::ncm::ApplicationId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IOverlayFunctions::SetAutoSleepTimeAndDimmingTimeEnabled(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IOverlayFunctions::SetGpuTimeSliceBoost(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IOverlayFunctions::SetScreenShotPermissionGlobally(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IOverlayFunctions::TerminateApplicationAndSetReason(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IProcessWindingController::CancelWindingReservation() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IProcessWindingController::GetLaunchReason(OUT nn::am::service::AppletProcessLaunchReason& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IProcessWindingController::OpenCallingLibraryApplet(OUT nn::am::service::ILibraryAppletAccessor * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ILibraryAppletAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IProcessWindingController::PopContext(OUT nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IProcessWindingController::PushContext(IN nn::am::service::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IProcessWindingController::ReserveToStartAndWaitAndUnwindThis(IN nn::am::service::ILibraryAppletAccessor * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IProcessWindingController::WindAndDoReserved() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::ApproveToDisplay() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::CreateManagedDisplayLayer(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::EnterFatalSection() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::Exit() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::GetCurrentIlluminance(OUT float32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::GetIdleTimeDetectionExtension(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::GetLibraryAppletLaunchableEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ISelfController::IsIlluminanceAvailable(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::LeaveFatalSection() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::LockExit() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::OverrideAutoSleepTimeAndDimmingTime(IN int32_t _0, IN int32_t _1, IN int32_t _2, IN int32_t _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::ReportUserIsActive() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetControllerFirmwareUpdateSection(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetFocusHandlingMode(IN bool _0, IN bool _1, IN bool _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetHandlesRequestToDisplay(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetIdleTimeDetectionExtension(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetInputDetectionSourceSet(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetMediaPlaybackState(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetOperationModeChangedNotification(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetOutOfFocusSuspendingEnabled(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetPerformanceModeChangedNotification(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetRequiresCaptureButtonShortPressedMessage(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetRestartMessageEnabled(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetScreenShotAppletIdentityInfo(IN nn::am::service::AppletIdentityInfo _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetScreenShotImageOrientation(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::SetScreenShotPermission(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::ISelfController::UnlockExit() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IStorage::Open(OUT nn::am::service::IStorageAccessor * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IStorageAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IStorage::OpenTransferStorage(OUT nn::am::service::ITransferStorageAccessor * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ITransferStorageAccessor(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IStorageAccessor::GetSize(OUT int64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IStorageAccessor::Read(IN int64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::IStorageAccessor::Write(IN int64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::am::service::ISystemAppletProxy::GetApplicationCreator(OUT nn::am::service::IApplicationCreator * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IApplicationCreator(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ISystemAppletProxy::GetAudioController(OUT nn::am::service::IAudioController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IAudioController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ISystemAppletProxy::GetCommonStateGetter(OUT nn::am::service::ICommonStateGetter * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ICommonStateGetter(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ISystemAppletProxy::GetDebugFunctions(OUT nn::am::service::IDebugFunctions * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IDebugFunctions(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ISystemAppletProxy::GetDisplayController(OUT nn::am::service::IDisplayController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IDisplayController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ISystemAppletProxy::GetGlobalStateController(OUT nn::am::service::IGlobalStateController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IGlobalStateController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ISystemAppletProxy::GetHomeMenuFunctions(OUT nn::am::service::IHomeMenuFunctions * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IHomeMenuFunctions(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ISystemAppletProxy::GetLibraryAppletCreator(OUT nn::am::service::ILibraryAppletCreator * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ILibraryAppletCreator(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ISystemAppletProxy::GetProcessWindingController(OUT nn::am::service::IProcessWindingController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IProcessWindingController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ISystemAppletProxy::GetSelfController(OUT nn::am::service::ISelfController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::ISelfController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ISystemAppletProxy::GetWindowController(OUT nn::am::service::IWindowController * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::am::service::IWindowController(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::ITransferStorageAccessor::GetHandle(OUT uint64_t& _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::am::service::ITransferStorageAccessor::GetSize(OUT int64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IWindow::Unknown12345() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IWindowController::AcquireForegroundRights() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IWindowController::CreateWindow(IN nn::am::service::WindowCreationOption _0, OUT nn::am::service::IWindow * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::am::service::IWindow(resp.move_handles[0]);
	return ret;
}
uint32_t nn::am::service::IWindowController::GetAppletResourceUserId(OUT nn::applet::AppletResourceUserId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IWindowController::RejectToChangeIntoBackground() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::am::service::IWindowController::ReleaseForegroundRights() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::aocsrv::detail {
	class IAddOnContentManager {
	public:
		IAddOnContentManager();
		uint32_t CountAddOnContent(IN uint64_t _0, IN gpid _1, OUT int32_t& _2);
		uint32_t CountAddOnContentByApplicationId(IN nn::ncm::ApplicationId _0, OUT int32_t& _1);
		uint32_t GetAddOnContentBaseId(IN uint64_t _0, IN gpid _1, OUT uint64_t& _2);
		uint32_t GetAddOnContentBaseIdByApplicationId(IN nn::ncm::ApplicationId _0, OUT uint64_t& _1);
		uint32_t ListAddOnContent(IN int32_t _0, IN int32_t _1, IN uint64_t _2, IN gpid _3, OUT int32_t& _4, OUT int32_t * _5, guint _5_size);
		uint32_t ListAddOnContentByApplicationId(IN int32_t _0, IN int32_t _1, IN nn::ncm::ApplicationId _2, OUT int32_t& _3, OUT int32_t * _4, guint _4_size);
		uint32_t PrepareAddOnContent(IN int32_t _0, IN uint64_t _1, IN gpid _2);
		uint32_t PrepareAddOnContentByApplicationId(IN int32_t _0, IN nn::ncm::ApplicationId _1);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::aocsrv::detail::IAddOnContentManager::CountAddOnContent(IN uint64_t _0, IN gpid _1, OUT int32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::aocsrv::detail::IAddOnContentManager::CountAddOnContentByApplicationId(IN nn::ncm::ApplicationId _0, OUT int32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::aocsrv::detail::IAddOnContentManager::GetAddOnContentBaseId(IN uint64_t _0, IN gpid _1, OUT uint64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::aocsrv::detail::IAddOnContentManager::GetAddOnContentBaseIdByApplicationId(IN nn::ncm::ApplicationId _0, OUT uint64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::aocsrv::detail::IAddOnContentManager::ListAddOnContent(IN int32_t _0, IN int32_t _1, IN uint64_t _2, IN gpid _3, OUT int32_t& _4, OUT int32_t * _5, guint _5_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::aocsrv::detail::IAddOnContentManager::ListAddOnContentByApplicationId(IN int32_t _0, IN int32_t _1, IN nn::ncm::ApplicationId _2, OUT int32_t& _3, OUT int32_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::aocsrv::detail::IAddOnContentManager::PrepareAddOnContent(IN int32_t _0, IN uint64_t _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::aocsrv::detail::IAddOnContentManager::PrepareAddOnContentByApplicationId(IN int32_t _0, IN nn::ncm::ApplicationId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::apm {
	class IManager {
	public:
		IManager();
		uint32_t GetPerformanceMode(OUT nn::apm::PerformanceMode& _0);
		uint32_t OpenSession(OUT nn::apm::ISession * _0);
	};
	class IManagerPrivileged {
	public:
		IManagerPrivileged();
		uint32_t OpenSession(OUT nn::apm::ISession * _0);
	};
	class ISession {
	public:
		ISession();
		uint32_t GetPerformanceConfiguration(IN nn::apm::PerformanceMode _0, OUT nn::apm::PerformanceConfiguration& _1);
		uint32_t SetPerformanceConfiguration(IN nn::apm::PerformanceMode _0, IN nn::apm::PerformanceConfiguration _1);
	};
	class ISystemManager {
	public:
		ISystemManager();
		uint32_t ClearLastThrottlingState();
		uint32_t GetLastThrottlingState(OUT nn::apm::ThrottlingState& _0);
		uint32_t GetPerformanceEvent(IN nn::apm::EventTarget _0, OUT KObject * _1);
		uint32_t GetThrottlingState(OUT nn::apm::ThrottlingState& _0);
		uint32_t RequestPerformanceMode(IN nn::apm::PerformanceMode _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::apm::IManager::GetPerformanceMode(OUT nn::apm::PerformanceMode& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::apm::IManager::OpenSession(OUT nn::apm::ISession * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::apm::ISession(resp.move_handles[0]);
	return ret;
}
uint32_t nn::apm::IManagerPrivileged::OpenSession(OUT nn::apm::ISession * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::apm::ISession(resp.move_handles[0]);
	return ret;
}
uint32_t nn::apm::ISession::GetPerformanceConfiguration(IN nn::apm::PerformanceMode _0, OUT nn::apm::PerformanceConfiguration& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::apm::ISession::SetPerformanceConfiguration(IN nn::apm::PerformanceMode _0, IN nn::apm::PerformanceConfiguration _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::apm::ISystemManager::ClearLastThrottlingState() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::apm::ISystemManager::GetLastThrottlingState(OUT nn::apm::ThrottlingState& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::apm::ThrottlingState>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::apm::ISystemManager::GetPerformanceEvent(IN nn::apm::EventTarget _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::apm::ISystemManager::GetThrottlingState(OUT nn::apm::ThrottlingState& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::apm::ThrottlingState>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::apm::ISystemManager::RequestPerformanceMode(IN nn::apm::PerformanceMode _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::arp::detail {
	class IReader {
	public:
		IReader();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
	};
	class IRegistrar {
	public:
		IRegistrar();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
	};
	class IWriter {
	public:
		IWriter();
		uint32_t Unknown0();
		uint32_t Unknown1();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::arp::detail::IReader::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::arp::detail::IReader::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::arp::detail::IReader::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::arp::detail::IReader::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::arp::detail::IRegistrar::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::arp::detail::IRegistrar::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::arp::detail::IRegistrar::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::arp::detail::IWriter::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::arp::detail::IWriter::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::audio::detail {
	class IAudioDebugManager {
	public:
		IAudioDebugManager();
		uint32_t Unknown0(IN uint32_t _0, IN uint64_t _1, IN KObject * _2);
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
	};
	class IAudioDevice {
	public:
		IAudioDevice();
		uint32_t Unknown0(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown1(IN uint32_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown10(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown11(OUT KObject * _0);
		uint32_t Unknown12(OUT KObject * _0);
		uint32_t Unknown2(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1);
		uint32_t Unknown3(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown4(OUT KObject * _0);
		uint32_t Unknown5(OUT uint32_t& _0);
		uint32_t Unknown6(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown7(IN uint32_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown8(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1);
	};
	class IAudioIn {
	public:
		IAudioIn();
		uint32_t Unknown0(OUT uint32_t& _0);
		uint32_t Unknown1();
		uint32_t Unknown10(IN uint64_t _0, IN KObject * _1, IN uint8_t * _2, guint _2_size);
		uint32_t Unknown2();
		uint32_t Unknown3(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown4(OUT KObject * _0);
		uint32_t Unknown5(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown6(IN uint64_t _0, OUT uint8_t& _1);
		uint32_t Unknown7(IN uint64_t _0, IN KObject * _1, IN uint8_t * _2, guint _2_size);
		uint32_t Unknown8(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown9(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
	};
	class IAudioInManager {
	public:
		IAudioInManager();
		uint32_t Unknown0(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown1(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN KObject * _3, IN uint8_t * _4, guint _4_size, OUT uint128_t& _5, OUT IUnknown * _6, OUT uint8_t * _7, guint _7_size);
		uint32_t Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown3(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN KObject * _3, IN uint8_t * _4, guint _4_size, OUT uint128_t& _5, OUT IUnknown * _6, OUT uint8_t * _7, guint _7_size);
		uint32_t Unknown4(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
	};
	class IAudioInManagerForApplet {
	public:
		IAudioInManagerForApplet();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2);
		uint32_t Unknown1(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2);
		uint32_t Unknown2(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown3(IN uint32_t _0, IN uint64_t _1, IN uint64_t _2);
	};
	class IAudioInManagerForDebugger {
	public:
		IAudioInManagerForDebugger();
		uint32_t Unknown0(IN uint64_t _0);
		uint32_t Unknown1(IN uint64_t _0);
	};
	class IAudioOut {
	public:
		IAudioOut();
		uint32_t Unknown0(OUT uint32_t& _0);
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown4(OUT KObject * _0);
		uint32_t Unknown5(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown6(IN uint64_t _0, OUT uint8_t& _1);
		uint32_t Unknown7(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown8(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
	};
	class IAudioOutManager {
	public:
		IAudioOutManager();
		uint32_t Unknown0(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown1(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN KObject * _3, IN uint8_t * _4, guint _4_size, OUT uint128_t& _5, OUT IUnknown * _6, OUT uint8_t * _7, guint _7_size);
		uint32_t Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown3(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN KObject * _3, IN uint8_t * _4, guint _4_size, OUT uint128_t& _5, OUT IUnknown * _6, OUT uint8_t * _7, guint _7_size);
	};
	class IAudioOutManagerForApplet {
	public:
		IAudioOutManagerForApplet();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2);
		uint32_t Unknown1(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2);
		uint32_t Unknown2(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown3(IN uint32_t _0, IN uint64_t _1, IN uint64_t _2);
	};
	class IAudioOutManagerForDebugger {
	public:
		IAudioOutManagerForDebugger();
		uint32_t Unknown0(IN uint64_t _0);
		uint32_t Unknown1(IN uint64_t _0);
	};
	class IAudioRenderer {
	public:
		IAudioRenderer();
		uint32_t Unknown0(OUT uint32_t& _0);
		uint32_t Unknown1(OUT uint32_t& _0);
		uint32_t Unknown10(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown11();
		uint32_t Unknown2(OUT uint32_t& _0);
		uint32_t Unknown3(OUT uint32_t& _0);
		uint32_t Unknown4(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7(OUT KObject * _0);
		uint32_t Unknown8(IN uint32_t _0);
		uint32_t Unknown9(OUT uint32_t& _0);
	};
	class IAudioRendererManager {
	public:
		IAudioRendererManager();
		uint32_t Unknown0(IN uint8_t * _0, IN uint64_t _1, IN uint64_t _2, IN gpid _3, IN KObject * _4, IN KObject * _5, OUT IUnknown * _6);
		uint32_t Unknown1(IN uint8_t * _0, OUT uint64_t& _1);
		uint32_t Unknown2(IN uint64_t _0, OUT IUnknown * _1);
		uint32_t Unknown3(IN uint8_t * _0, IN uint64_t _1, IN uint64_t _2, IN uint64_t _3, IN gpid _4, IN KObject * _5, OUT IUnknown * _6);
	};
	class IAudioRendererManagerForApplet {
	public:
		IAudioRendererManagerForApplet();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2);
		uint32_t Unknown1(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2);
		uint32_t Unknown2(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown3(IN uint32_t _0, IN uint64_t _1, IN uint64_t _2);
		uint32_t Unknown4(IN uint64_t _0);
		uint32_t Unknown5(IN uint64_t _0);
	};
	class IAudioRendererManagerForDebugger {
	public:
		IAudioRendererManagerForDebugger();
		uint32_t Unknown0(IN uint64_t _0);
		uint32_t Unknown1(IN uint64_t _0);
	};
	class IFinalOutputRecorder {
	public:
		IFinalOutputRecorder();
		uint32_t Unknown0(OUT uint32_t& _0);
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown4(OUT KObject * _0);
		uint32_t Unknown5(OUT uint32_t& _0, OUT uint64_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown6(IN uint64_t _0, OUT uint8_t& _1);
		uint32_t Unknown7(IN uint64_t _0, OUT uint64_t& _1);
		uint32_t Unknown8(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown9(OUT uint32_t& _0, OUT uint64_t& _1, OUT uint8_t * _2, guint _2_size);
	};
	class IFinalOutputRecorderManager {
	public:
		IFinalOutputRecorderManager();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, IN KObject * _2, OUT uint128_t& _3, OUT IUnknown * _4);
	};
	class IFinalOutputRecorderManagerForApplet {
	public:
		IFinalOutputRecorderManagerForApplet();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2);
		uint32_t Unknown1(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2);
	};
	class IFinalOutputRecorderManagerForDebugger {
	public:
		IFinalOutputRecorderManagerForDebugger();
		uint32_t Unknown0(IN uint64_t _0);
		uint32_t Unknown1(IN uint64_t _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::audio::detail::IAudioDebugManager::Unknown0(IN uint32_t _0, IN uint64_t _1, IN KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioDebugManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioDebugManager::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioDebugManager::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown0(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown1(IN uint32_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown10(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown11(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown12(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown2(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown3(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown4(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown5(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown6(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown7(IN uint32_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioDevice::Unknown8(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioIn::Unknown0(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioIn::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioIn::Unknown10(IN uint64_t _0, IN KObject * _1, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioIn::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioIn::Unknown3(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioIn::Unknown4(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioIn::Unknown5(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioIn::Unknown6(IN uint64_t _0, OUT uint8_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioIn::Unknown7(IN uint64_t _0, IN KObject * _1, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioIn::Unknown8(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioIn::Unknown9(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioInManager::Unknown0(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioInManager::Unknown1(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN KObject * _3, IN uint8_t * _4, guint _4_size, OUT uint128_t& _5, OUT IUnknown * _6, OUT uint8_t * _7, guint _7_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_6 OMG = new IUnknown(resp.move_handles[0]);
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::audio::detail::IAudioInManager::Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioInManager::Unknown3(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN KObject * _3, IN uint8_t * _4, guint _4_size, OUT uint128_t& _5, OUT IUnknown * _6, OUT uint8_t * _7, guint _7_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x22, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_6 OMG = new IUnknown(resp.move_handles[0]);
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::audio::detail::IAudioInManager::Unknown4(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioInManagerForApplet::Unknown0(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioInManagerForApplet::Unknown1(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioInManagerForApplet::Unknown2(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioInManagerForApplet::Unknown3(IN uint32_t _0, IN uint64_t _1, IN uint64_t _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioInManagerForDebugger::Unknown0(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioInManagerForDebugger::Unknown1(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioOut::Unknown0(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioOut::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioOut::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioOut::Unknown3(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioOut::Unknown4(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioOut::Unknown5(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioOut::Unknown6(IN uint64_t _0, OUT uint8_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioOut::Unknown7(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioOut::Unknown8(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioOutManager::Unknown0(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioOutManager::Unknown1(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN KObject * _3, IN uint8_t * _4, guint _4_size, OUT uint128_t& _5, OUT IUnknown * _6, OUT uint8_t * _7, guint _7_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_6 OMG = new IUnknown(resp.move_handles[0]);
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::audio::detail::IAudioOutManager::Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IAudioOutManager::Unknown3(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN KObject * _3, IN uint8_t * _4, guint _4_size, OUT uint128_t& _5, OUT IUnknown * _6, OUT uint8_t * _7, guint _7_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x22, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_6 OMG = new IUnknown(resp.move_handles[0]);
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::audio::detail::IAudioOutManagerForApplet::Unknown0(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioOutManagerForApplet::Unknown1(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioOutManagerForApplet::Unknown2(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioOutManagerForApplet::Unknown3(IN uint32_t _0, IN uint64_t _1, IN uint64_t _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioOutManagerForDebugger::Unknown0(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioOutManagerForDebugger::Unknown1(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown0(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown1(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown10(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x22, 0, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(0x22, 1, temp8);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	ctu->cpu.writemem(temp7, temp9, temp8);
	delete[] temp9;
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown2(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown3(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown4(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(6, 1, temp8);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	ctu->cpu.writemem(temp7, temp9, temp8);
	delete[] temp9;
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown7(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown8(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRenderer::Unknown9(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManager::Unknown0(IN uint8_t * _0, IN uint64_t _1, IN uint64_t _2, IN gpid _3, IN KObject * _4, IN KObject * _5, OUT IUnknown * _6) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_6 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManager::Unknown1(IN uint8_t * _0, OUT uint64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManager::Unknown2(IN uint64_t _0, OUT IUnknown * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManager::Unknown3(IN uint8_t * _0, IN uint64_t _1, IN uint64_t _2, IN uint64_t _3, IN gpid _4, IN KObject * _5, OUT IUnknown * _6) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_6 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManagerForApplet::Unknown0(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManagerForApplet::Unknown1(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManagerForApplet::Unknown2(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManagerForApplet::Unknown3(IN uint32_t _0, IN uint64_t _1, IN uint64_t _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManagerForApplet::Unknown4(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManagerForApplet::Unknown5(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManagerForDebugger::Unknown0(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IAudioRendererManagerForDebugger::Unknown1(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorder::Unknown0(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorder::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorder::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorder::Unknown3(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorder::Unknown4(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorder::Unknown5(OUT uint32_t& _0, OUT uint64_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorder::Unknown6(IN uint64_t _0, OUT uint8_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorder::Unknown7(IN uint64_t _0, OUT uint64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorder::Unknown8(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorder::Unknown9(OUT uint32_t& _0, OUT uint64_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorderManager::Unknown0(IN uint64_t _0, IN uint64_t _1, IN KObject * _2, OUT uint128_t& _3, OUT IUnknown * _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_4 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorderManagerForApplet::Unknown0(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorderManagerForApplet::Unknown1(IN uint64_t _0, IN uint64_t _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorderManagerForDebugger::Unknown0(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audio::detail::IFinalOutputRecorderManagerForDebugger::Unknown1(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::audioctrl::detail {
	class IAudioController {
	public:
		IAudioController();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown14();
		uint32_t Unknown15();
		uint32_t Unknown16();
		uint32_t Unknown17();
		uint32_t Unknown18();
		uint32_t Unknown19();
		uint32_t Unknown2();
		uint32_t Unknown20();
		uint32_t Unknown21();
		uint32_t Unknown22();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::audioctrl::detail::IAudioController::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown14() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown15() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown16() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown17() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown18() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown19() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown20() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown21() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown22() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::audioctrl::detail::IAudioController::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::bcat::detail::ipc {
	class IBcatService {
	public:
		IBcatService();
		uint32_t BlockDeliveryTask(IN nn::ApplicationId _0);
		uint32_t ClearDeliveryCacheStorage(IN nn::ApplicationId _0);
		uint32_t EnumerateBackgroundDeliveryTask(OUT int32_t& _0, OUT nn::bcat::TaskInfo * _1, guint _1_size);
		uint32_t GetDeliveryList(IN nn::ApplicationId _0, OUT uint64_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t GetPushNotificationLog(OUT int32_t& _0, OUT nn::bcat::PushNotificationLog * _1, guint _1_size);
		uint32_t RegisterBackgroundDeliveryTask(IN uint32_t _0, IN nn::ApplicationId _1);
		uint32_t RequestSyncDeliveryCache(OUT nn::bcat::detail::ipc::IDeliveryCacheProgressService * _0);
		uint32_t RequestSyncDeliveryCacheWithApplicationId(IN uint32_t _0, IN nn::ApplicationId _1, OUT nn::bcat::detail::ipc::IDeliveryCacheProgressService * _2);
		uint32_t SetPassphrase(IN nn::ApplicationId _0, IN int8_t * _1, guint _1_size);
		uint32_t UnblockDeliveryTask(IN nn::ApplicationId _0);
		uint32_t UnregisterBackgroundDeliveryTask(IN nn::ApplicationId _0);
	};
	class IDeliveryCacheDirectoryService {
	public:
		IDeliveryCacheDirectoryService();
		uint32_t GetCount(OUT int32_t& _0);
		uint32_t Open(IN nn::bcat::DirectoryName _0);
		uint32_t Read(OUT int32_t& _0, OUT nn::bcat::DeliveryCacheDirectoryEntry * _1, guint _1_size);
	};
	class IDeliveryCacheFileService {
	public:
		IDeliveryCacheFileService();
		uint32_t GetDigest(OUT nn::bcat::Digest& _0);
		uint32_t GetSize(OUT int64_t& _0);
		uint32_t Open(IN nn::bcat::DirectoryName _0, IN nn::bcat::FileName _1);
		uint32_t Read(IN int64_t _0, OUT uint64_t& _1, OUT uint8_t * _2, guint _2_size);
	};
	class IDeliveryCacheProgressService {
	public:
		IDeliveryCacheProgressService();
		uint32_t GetEvent(OUT KObject * _0);
		uint32_t GetImpl(OUT nn::bcat::detail::DeliveryCacheProgressImpl * _0, guint _0_size);
	};
	class IDeliveryCacheStorageService {
	public:
		IDeliveryCacheStorageService();
		uint32_t CreateDirectoryService(OUT nn::bcat::detail::ipc::IDeliveryCacheDirectoryService * _0);
		uint32_t CreateFileService(OUT nn::bcat::detail::ipc::IDeliveryCacheFileService * _0);
		uint32_t EnumerateDeliveryCacheDirectory(OUT int32_t& _0, OUT nn::bcat::DirectoryName * _1, guint _1_size);
	};
	class IServiceCreator {
	public:
		IServiceCreator();
		uint32_t CreateBcatService(IN uint64_t _0, IN gpid _1, OUT nn::bcat::detail::ipc::IBcatService * _2);
		uint32_t CreateDeliveryCacheStorageService(IN uint64_t _0, IN gpid _1, OUT nn::bcat::detail::ipc::IDeliveryCacheStorageService * _2);
		uint32_t CreateDeliveryCacheStorageServiceWithApplicationId(IN nn::ApplicationId _0, OUT nn::bcat::detail::ipc::IDeliveryCacheStorageService * _1);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::bcat::detail::ipc::IBcatService::BlockDeliveryTask(IN nn::ApplicationId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IBcatService::ClearDeliveryCacheStorage(IN nn::ApplicationId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IBcatService::EnumerateBackgroundDeliveryTask(OUT int32_t& _0, OUT nn::bcat::TaskInfo * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::bcat::detail::ipc::IBcatService::GetDeliveryList(IN nn::ApplicationId _0, OUT uint64_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::bcat::detail::ipc::IBcatService::GetPushNotificationLog(OUT int32_t& _0, OUT nn::bcat::PushNotificationLog * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::bcat::detail::ipc::IBcatService::RegisterBackgroundDeliveryTask(IN uint32_t _0, IN nn::ApplicationId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IBcatService::RequestSyncDeliveryCache(OUT nn::bcat::detail::ipc::IDeliveryCacheProgressService * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::bcat::detail::ipc::IDeliveryCacheProgressService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IBcatService::RequestSyncDeliveryCacheWithApplicationId(IN uint32_t _0, IN nn::ApplicationId _1, OUT nn::bcat::detail::ipc::IDeliveryCacheProgressService * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::bcat::detail::ipc::IDeliveryCacheProgressService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IBcatService::SetPassphrase(IN nn::ApplicationId _0, IN int8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::bcat::detail::ipc::IBcatService::UnblockDeliveryTask(IN nn::ApplicationId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IBcatService::UnregisterBackgroundDeliveryTask(IN nn::ApplicationId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheDirectoryService::GetCount(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheDirectoryService::Open(IN nn::bcat::DirectoryName _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheDirectoryService::Read(OUT int32_t& _0, OUT nn::bcat::DeliveryCacheDirectoryEntry * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheFileService::GetDigest(OUT nn::bcat::Digest& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheFileService::GetSize(OUT int64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheFileService::Open(IN nn::bcat::DirectoryName _0, IN nn::bcat::FileName _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheFileService::Read(IN int64_t _0, OUT uint64_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheProgressService::GetEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheProgressService::GetImpl(OUT nn::bcat::detail::DeliveryCacheProgressImpl * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheStorageService::CreateDirectoryService(OUT nn::bcat::detail::ipc::IDeliveryCacheDirectoryService * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::bcat::detail::ipc::IDeliveryCacheDirectoryService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheStorageService::CreateFileService(OUT nn::bcat::detail::ipc::IDeliveryCacheFileService * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::bcat::detail::ipc::IDeliveryCacheFileService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IDeliveryCacheStorageService::EnumerateDeliveryCacheDirectory(OUT int32_t& _0, OUT nn::bcat::DirectoryName * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::bcat::detail::ipc::IServiceCreator::CreateBcatService(IN uint64_t _0, IN gpid _1, OUT nn::bcat::detail::ipc::IBcatService * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::bcat::detail::ipc::IBcatService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IServiceCreator::CreateDeliveryCacheStorageService(IN uint64_t _0, IN gpid _1, OUT nn::bcat::detail::ipc::IDeliveryCacheStorageService * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::bcat::detail::ipc::IDeliveryCacheStorageService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::bcat::detail::ipc::IServiceCreator::CreateDeliveryCacheStorageServiceWithApplicationId(IN nn::ApplicationId _0, OUT nn::bcat::detail::ipc::IDeliveryCacheStorageService * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::bcat::detail::ipc::IDeliveryCacheStorageService(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::bgtc {
	class IStateControlService {
	public:
		IStateControlService();
	};
	class ITaskService {
	public:
		ITaskService();
		uint32_t Unknown14(OUT KObject * _0);
		uint32_t Unknown3(OUT KObject * _0);
		uint32_t Unknown5(IN uint8_t * _0, guint _0_size);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::bgtc::ITaskService::Unknown14(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::bgtc::ITaskService::Unknown3(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::bgtc::ITaskService::Unknown5(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::bluetooth {
	class IBluetoothDriver {
	public:
		IBluetoothDriver();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown14();
		uint32_t Unknown15();
		uint32_t Unknown16();
		uint32_t Unknown17();
		uint32_t Unknown18();
		uint32_t Unknown19();
		uint32_t Unknown2();
		uint32_t Unknown20();
		uint32_t Unknown21();
		uint32_t Unknown22();
		uint32_t Unknown23();
		uint32_t Unknown24();
		uint32_t Unknown25();
		uint32_t Unknown26();
		uint32_t Unknown27();
		uint32_t Unknown28();
		uint32_t Unknown29();
		uint32_t Unknown3();
		uint32_t Unknown30();
		uint32_t Unknown31();
		uint32_t Unknown32();
		uint32_t Unknown33();
		uint32_t Unknown34();
		uint32_t Unknown35();
		uint32_t Unknown36();
		uint32_t Unknown37();
		uint32_t Unknown38();
		uint32_t Unknown39();
		uint32_t Unknown4();
		uint32_t Unknown40();
		uint32_t Unknown41();
		uint32_t Unknown42();
		uint32_t Unknown43();
		uint32_t Unknown44();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::bluetooth::IBluetoothDriver::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown14() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown15() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown16() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown17() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown18() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown19() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown20() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown21() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown22() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown23() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown24() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown25() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown26() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown27() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown28() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown29() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown30() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown31() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown32() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown33() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown34() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown35() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown36() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown37() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown38() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown39() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown40() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown41() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown42() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown43() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown44() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bluetooth::IBluetoothDriver::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::bpc {
	class IBoardPowerControlManager {
	public:
		IBoardPowerControlManager();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
	class IRtcManager {
	public:
		IRtcManager();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::bpc::IBoardPowerControlManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IBoardPowerControlManager::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IRtcManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IRtcManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IRtcManager::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IRtcManager::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bpc::IRtcManager::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::bsdsocket::cfg {
	class ServerInterface {
	public:
		ServerInterface();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::bsdsocket::cfg::ServerInterface::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::btm {
	class IBtm {
	public:
		IBtm();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown14();
		uint32_t Unknown15();
		uint32_t Unknown16();
		uint32_t Unknown17();
		uint32_t Unknown18();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
	class IBtmDebug {
	public:
		IBtmDebug();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
	};
	class IBtmSystem {
	public:
		IBtmSystem();
		uint32_t Unknown0();
	};
	class IBtmSystemCore {
	public:
		IBtmSystemCore();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::btm::IBtm::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown14() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown15() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown16() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown17() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown18() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtm::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmDebug::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmDebug::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmDebug::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmDebug::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmDebug::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmDebug::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmDebug::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmDebug::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmDebug::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmSystem::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmSystemCore::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmSystemCore::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmSystemCore::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmSystemCore::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmSystemCore::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmSystemCore::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmSystemCore::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmSystemCore::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmSystemCore::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::btm::IBtmSystemCore::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::capsrv::sf {
	class IAlbumAccessorService {
	public:
		IAlbumAccessorService();
	};
	class IAlbumControlService {
	public:
		IAlbumControlService();
	};
	class IScreenShotApplicationService {
	public:
		IScreenShotApplicationService();
		uint32_t SaveScreenShot(IN uint32_t _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3, IN uint8_t * _4, guint _4_size, OUT nn::capsrv::ApplicationAlbumEntry& _5);
		uint32_t SaveScreenShotEx0(IN nn::capsrv::detail::ScreenShotAttributeEx0 _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3, IN uint8_t * _4, guint _4_size, OUT nn::capsrv::ApplicationAlbumEntry& _5);
	};
	class IScreenShotControlService {
	public:
		IScreenShotControlService();
		uint32_t Unknown1();
		uint32_t Unknown1001();
		uint32_t Unknown1002();
		uint32_t Unknown1003();
		uint32_t Unknown1011();
		uint32_t Unknown1012();
		uint32_t Unknown1201();
		uint32_t Unknown1202();
		uint32_t Unknown1203();
		uint32_t Unknown2();
	};
	class IScreenShotService {
	public:
		IScreenShotService();
		uint32_t Unknown201();
		uint32_t Unknown202();
		uint32_t Unknown203();
		uint32_t Unknown204();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::capsrv::sf::IScreenShotApplicationService::SaveScreenShot(IN uint32_t _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3, IN uint8_t * _4, guint _4_size, OUT nn::capsrv::ApplicationAlbumEntry& _5) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x45, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto temp4 = resp.getDataPointer<nn::capsrv::ApplicationAlbumEntry>(8);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotApplicationService::SaveScreenShotEx0(IN nn::capsrv::detail::ScreenShotAttributeEx0 _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3, IN uint8_t * _4, guint _4_size, OUT nn::capsrv::ApplicationAlbumEntry& _5) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x45, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto temp4 = resp.getDataPointer<nn::capsrv::ApplicationAlbumEntry>(8);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotControlService::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotControlService::Unknown1001() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotControlService::Unknown1002() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotControlService::Unknown1003() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotControlService::Unknown1011() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotControlService::Unknown1012() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotControlService::Unknown1201() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotControlService::Unknown1202() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotControlService::Unknown1203() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotControlService::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotService::Unknown201() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotService::Unknown202() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotService::Unknown203() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::capsrv::sf::IScreenShotService::Unknown204() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::cec {
	class ICecManager {
	public:
		ICecManager();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::cec::ICecManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::cec::ICecManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::cec::ICecManager::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::cec::ICecManager::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::cec::ICecManager::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::cec::ICecManager::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::cec::ICecManager::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::codec::detail {
	class IHardwareOpusDecoder {
	public:
		IHardwareOpusDecoder();
		uint32_t Unknown0(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t Unknown1(IN uint8_t * _0, guint _0_size);
		uint32_t Unknown2(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t Unknown3(IN uint8_t * _0, guint _0_size);
	};
	class IHardwareOpusDecoderManager {
	public:
		IHardwareOpusDecoderManager();
		uint32_t Unknown0(IN uint64_t _0, IN uint32_t _1, IN KObject * _2, OUT IUnknown * _3);
		uint32_t Unknown1(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown2(IN uint32_t _0, IN KObject * _1, IN uint8_t * _2, guint _2_size, OUT IUnknown * _3);
		uint32_t Unknown3(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::codec::detail::IHardwareOpusDecoder::Unknown0(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::codec::detail::IHardwareOpusDecoder::Unknown1(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::codec::detail::IHardwareOpusDecoder::Unknown2(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::codec::detail::IHardwareOpusDecoder::Unknown3(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::codec::detail::IHardwareOpusDecoderManager::Unknown0(IN uint64_t _0, IN uint32_t _1, IN KObject * _2, OUT IUnknown * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_3 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::codec::detail::IHardwareOpusDecoderManager::Unknown1(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::codec::detail::IHardwareOpusDecoderManager::Unknown2(IN uint32_t _0, IN KObject * _1, IN uint8_t * _2, guint _2_size, OUT IUnknown * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_3 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::codec::detail::IHardwareOpusDecoderManager::Unknown3(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::erpt::sf {
	class IContext {
	public:
		IContext();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
	};
	class IManager {
	public:
		IManager();
		uint32_t Unknown0();
		uint32_t Unknown1();
	};
	class IReport {
	public:
		IReport();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
	};
	class ISession {
	public:
		ISession();
		uint32_t Unknown0();
		uint32_t Unknown1();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::erpt::sf::IContext::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IContext::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IContext::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IContext::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IContext::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IContext::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IReport::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IReport::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IReport::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IReport::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IReport::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::IReport::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::ISession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::erpt::sf::ISession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::es {
	class IETicketService {
	public:
		IETicketService();
	};
}
#ifdef DEFINE_CALLERS
#endif // DEFINE_CALLERS
namespace nn::eth::sf {
	class IEthInterface {
	public:
		IEthInterface();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
	};
	class IEthInterfaceGroup {
	public:
		IEthInterfaceGroup();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::eth::sf::IEthInterface::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eth::sf::IEthInterface::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eth::sf::IEthInterface::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eth::sf::IEthInterface::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eth::sf::IEthInterface::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eth::sf::IEthInterface::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eth::sf::IEthInterfaceGroup::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eth::sf::IEthInterfaceGroup::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eth::sf::IEthInterfaceGroup::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eth::sf::IEthInterfaceGroup::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eth::sf::IEthInterfaceGroup::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::eupld::sf {
	class IControl {
	public:
		IControl();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
	};
	class IRequest {
	public:
		IRequest();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::eupld::sf::IControl::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eupld::sf::IControl::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eupld::sf::IControl::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eupld::sf::IControl::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eupld::sf::IRequest::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eupld::sf::IRequest::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eupld::sf::IRequest::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eupld::sf::IRequest::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eupld::sf::IRequest::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::eupld::sf::IRequest::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::fan::detail {
	class IController {
	public:
		IController();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
	};
	class IManager {
	public:
		IManager();
		uint32_t Unknown0();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::fan::detail::IController::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fan::detail::IController::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fan::detail::IController::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fan::detail::IController::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fan::detail::IController::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fan::detail::IController::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fan::detail::IController::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fan::detail::IController::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fan::detail::IManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::fatalsrv {
	class IPrivateService {
	public:
		IPrivateService();
		uint32_t Unknown0();
	};
	class IService {
	public:
		IService();
		uint32_t TransitionToFatalError(IN uint64_t errorCode, IN uint64_t _1, IN uint8_t * errorBuf, guint errorBuf_size, IN gpid _3);
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2);
		uint32_t Unknown1(IN uint64_t _0, IN uint64_t _1, IN gpid _2);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::fatalsrv::IPrivateService::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fatalsrv::IService::TransitionToFatalError(IN uint64_t errorCode, IN uint64_t _1, IN uint8_t * errorBuf, guint errorBuf_size, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x15, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fatalsrv::IService::Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fatalsrv::IService::Unknown1(IN uint64_t _0, IN uint64_t _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::fgm::sf {
	class IDebugger {
	public:
		IDebugger();
		uint32_t Cancel();
		uint32_t Initialize(IN uint64_t _0, IN KObject * _1, OUT KObject * _2);
		uint32_t Read(OUT uint32_t& _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size);
	};
	class IRequest {
	public:
		IRequest();
		uint32_t Cancel();
		uint32_t Get(OUT uint32_t& _0);
		uint32_t Initialize(IN nn::fgm::Module _0, IN uint64_t _1, IN gpid _2, OUT KObject * _3);
		uint32_t Set(IN uint32_t _0, IN uint32_t _1);
	};
	class ISession {
	public:
		ISession();
		uint32_t Initialize(OUT nn::fgm::sf::IRequest * _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::fgm::sf::IDebugger::Cancel() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fgm::sf::IDebugger::Initialize(IN uint64_t _0, IN KObject * _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::fgm::sf::IDebugger::Read(OUT uint32_t& _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fgm::sf::IRequest::Cancel() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fgm::sf::IRequest::Get(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fgm::sf::IRequest::Initialize(IN nn::fgm::Module _0, IN uint64_t _1, IN gpid _2, OUT KObject * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::fgm::sf::IRequest::Set(IN uint32_t _0, IN uint32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fgm::sf::ISession::Initialize(OUT nn::fgm::sf::IRequest * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::fgm::sf::IRequest(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::friends::detail::ipc {
	class IFriendService {
	public:
		IFriendService();
		uint32_t AcceptFriendRequest(IN nn::account::Uid _0, IN nn::friends::RequestId _1);
		uint32_t AddFacedFriendRequest(IN nn::friends::FacedFriendRequestRegistrationKey _0, IN nn::account::Nickname _1, IN nn::account::Uid _2, IN uint8_t * _3, guint _3_size);
		uint32_t AddFacedFriendRequestForApplication(IN nn::friends::FacedFriendRequestRegistrationKey _0, IN nn::account::Nickname _1, IN nn::account::Uid _2, IN uint64_t _3, IN gpid _4, IN uint8_t * _5, guint _5_size, IN nn::friends::InAppScreenName * _6, guint _6_size, IN nn::friends::InAppScreenName * _7, guint _7_size);
		uint32_t AddPlayHistory(IN nn::account::Uid _0, IN uint64_t _1, IN gpid _2, IN nn::friends::PlayHistoryRegistrationKey * _3, guint _3_size, IN nn::friends::InAppScreenName * _4, guint _4_size, IN nn::friends::InAppScreenName * _5, guint _5_size);
		uint32_t BlockUser(IN int32_t _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2);
		uint32_t BlockUserWithApplicationInfo(IN int32_t _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2, IN nn::friends::ApplicationInfo _3, IN nn::friends::InAppScreenName * _4, guint _4_size);
		uint32_t Cancel();
		uint32_t CancelFacedFriendRequest(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1);
		uint32_t CancelFriendRequest(IN nn::account::Uid _0, IN nn::friends::RequestId _1);
		uint32_t ChangeFriendFavoriteFlag(IN bool _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2);
		uint32_t ChangeFriendOnlineNotificationFlag(IN bool _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2);
		uint32_t ChangeFriendRequestReception(IN bool _0, IN nn::account::Uid _1);
		uint32_t ChangePlayLogPermission(IN int32_t _0, IN nn::account::Uid _1);
		uint32_t ChangePresencePermission(IN int32_t _0, IN nn::account::Uid _1);
		uint32_t ClearPlayLog(IN nn::account::Uid _0);
		uint32_t DeclareCloseOnlinePlaySession(IN nn::account::Uid _0);
		uint32_t DeclareOpenOnlinePlaySession(IN nn::account::Uid _0);
		uint32_t DeleteFriend(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1);
		uint32_t DeleteNetworkServiceAccountCache(IN nn::account::Uid _0);
		uint32_t DeletePlayHistory(IN nn::account::Uid _0);
		uint32_t DropFriendNewlyFlag(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1);
		uint32_t DropFriendNewlyFlags(IN nn::account::Uid _0);
		uint32_t GetBlockedUserList(IN int32_t _0, IN nn::account::Uid _1, OUT int32_t& _2, OUT nn::friends::detail::BlockedUserImpl * _3, guint _3_size);
		uint32_t GetBlockedUserListIds(IN int32_t _0, IN nn::account::Uid _1, OUT int32_t& _2, OUT nn::account::NetworkServiceAccountId * _3, guint _3_size);
		uint32_t GetCompletionEvent(OUT KObject * _0);
		uint32_t GetExternalApplicationCatalog(IN nn::settings::LanguageCode _0, IN nn::friends::ExternalApplicationCatalogId _1, OUT nn::friends::ExternalApplicationCatalog * _2, guint _2_size);
		uint32_t GetFacedFriendRequestProfileImage(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, OUT int32_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t GetFacedFriendRequestProfileImageFromPath(IN int8_t * _0, guint _0_size, OUT int32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t GetFacedFriendRequestRegistrationKey(IN nn::account::Uid _0, OUT nn::friends::FacedFriendRequestRegistrationKey& _1);
		uint32_t GetFriendCandidateList(IN int32_t _0, IN nn::account::Uid _1, OUT int32_t& _2, OUT nn::friends::detail::FriendCandidateImpl * _3, guint _3_size);
		uint32_t GetFriendCount(IN nn::account::Uid _0, IN nn::friends::detail::ipc::SizedFriendFilter _1, IN uint64_t _2, IN gpid _3, OUT int32_t& _4);
		uint32_t GetFriendDetailedInfo(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, OUT nn::friends::detail::FriendDetailedInfoImpl * _2, guint _2_size);
		uint32_t GetFriendList(IN int32_t _0, IN nn::account::Uid _1, IN nn::friends::detail::ipc::SizedFriendFilter _2, IN uint64_t _3, IN gpid _4, OUT int32_t& _5, OUT nn::friends::detail::FriendImpl * _6, guint _6_size);
		uint32_t GetFriendListIds(IN int32_t _0, IN nn::account::Uid _1, IN nn::friends::detail::ipc::SizedFriendFilter _2, IN uint64_t _3, IN gpid _4, OUT int32_t& _5, OUT nn::account::NetworkServiceAccountId * _6, guint _6_size);
		uint32_t GetFriendProfileImage(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, OUT int32_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t GetFriendRequestList(IN int32_t _0, IN int32_t _1, IN nn::account::Uid _2, OUT int32_t& _3, OUT nn::friends::detail::FriendRequestImpl * _4, guint _4_size);
		uint32_t GetNewlyFriendCount(IN nn::account::Uid _0, OUT int32_t& _1);
		uint32_t GetNintendoNetworkIdInfo(IN int32_t _0, IN nn::account::Uid _1, OUT int32_t& _2, OUT nn::friends::NintendoNetworkIdUserInfo * _3, guint _3_size, OUT nn::friends::detail::NintendoNetworkIdFriendImpl * _4, guint _4_size);
		uint32_t GetPlayHistoryList(IN int32_t _0, IN nn::account::Uid _1, OUT int32_t& _2, OUT nn::friends::detail::PlayHistoryImpl * _3, guint _3_size);
		uint32_t GetPlayHistoryRegistrationKey(IN bool _0, IN nn::account::Uid _1, OUT nn::friends::PlayHistoryRegistrationKey * _2, guint _2_size);
		uint32_t GetPlayHistoryRegistrationKeyWithNetworkServiceAccountId(IN bool _0, IN nn::account::NetworkServiceAccountId _1, OUT nn::friends::PlayHistoryRegistrationKey * _2, guint _2_size);
		uint32_t GetPlayHistoryStatistics(IN nn::account::Uid _0, OUT nn::friends::PlayHistoryStatistics& _1);
		uint32_t GetProfileExtraFromFriendCode(IN nn::friends::FriendCode _0, IN nn::account::Uid _1, OUT nn::friends::detail::ProfileExtraImpl * _2, guint _2_size);
		uint32_t GetProfileExtraList(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId * _1, guint _1_size, OUT nn::friends::detail::ProfileExtraImpl * _2, guint _2_size);
		uint32_t GetProfileImageUrl(IN nn::friends::Url _0, IN int32_t _1, OUT nn::friends::Url& _2);
		uint32_t GetProfileList(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId * _1, guint _1_size, OUT nn::friends::detail::ProfileImpl * _2, guint _2_size);
		uint32_t GetReceivedFriendRequestCount(IN nn::account::Uid _0, OUT int32_t& _1, OUT int32_t& _2);
		uint32_t GetRelationship(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, OUT nn::friends::Relationship& _2);
		uint32_t GetUserPresenceView(IN nn::account::Uid _0, OUT nn::friends::detail::UserPresenceViewImpl * _1, guint _1_size);
		uint32_t IssueFriendCode(IN nn::account::Uid _0);
		uint32_t LoadFriendSetting(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, OUT nn::friends::detail::FriendSettingImpl * _2, guint _2_size);
		uint32_t LoadUserSetting(IN nn::account::Uid _0, OUT nn::friends::detail::UserSettingImpl * _1, guint _1_size);
		uint32_t ReadFriendRequest(IN nn::account::Uid _0, IN nn::friends::RequestId _1);
		uint32_t RejectFriendRequest(IN nn::account::Uid _0, IN nn::friends::RequestId _1);
		uint32_t RequestListSummaryOverlayNotification();
		uint32_t RequestSyncFriendList(IN nn::account::Uid _0);
		uint32_t ResendFacedFriendRequest(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1);
		uint32_t SendFriendRequest(IN int32_t _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2);
		uint32_t SendFriendRequestForApplication(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, IN uint64_t _2, IN gpid _3, IN nn::friends::InAppScreenName * _4, guint _4_size, IN nn::friends::InAppScreenName * _5, guint _5_size);
		uint32_t SendFriendRequestWithApplicationInfo(IN int32_t _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2, IN nn::friends::ApplicationInfo _3, IN nn::friends::InAppScreenName * _4, guint _4_size, IN nn::friends::InAppScreenName * _5, guint _5_size);
		uint32_t SendFriendRequestWithExternalApplicationCatalogId(IN int32_t _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2, IN nn::friends::ExternalApplicationCatalogId _3, IN nn::friends::InAppScreenName * _4, guint _4_size, IN nn::friends::InAppScreenName * _5, guint _5_size);
		uint32_t SendFriendRequestWithNintendoNetworkIdInfo(IN nn::friends::MiiName _0, IN nn::friends::MiiImageUrlParam _1, IN nn::friends::MiiName _2, IN nn::friends::MiiImageUrlParam _3, IN int32_t _4, IN nn::account::Uid _5, IN nn::account::NetworkServiceAccountId _6);
		uint32_t SyncBlockedUserList(IN nn::account::Uid _0);
		uint32_t SyncFriendList(IN nn::account::Uid _0);
		uint32_t SyncUserSetting(IN nn::account::Uid _0);
		uint32_t UnblockUser(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1);
		uint32_t UpdateFriendInfo(IN nn::account::Uid _0, IN uint64_t _1, IN gpid _2, IN nn::account::NetworkServiceAccountId * _3, guint _3_size, OUT nn::friends::detail::FriendImpl * _4, guint _4_size);
		uint32_t UpdateUserPresence(IN nn::account::Uid _0, IN uint64_t _1, IN gpid _2, IN nn::friends::detail::UserPresenceImpl * _3, guint _3_size);
	};
	class INotificationService {
	public:
		INotificationService();
		uint32_t Clear();
		uint32_t GetEvent(OUT KObject * _0);
		uint32_t Pop(OUT nn::friends::detail::ipc::SizedNotificationInfo& _0);
	};
	class IServiceCreator {
	public:
		IServiceCreator();
		uint32_t CreateFriendService(OUT nn::friends::detail::ipc::IFriendService * _0);
		uint32_t CreateNotificationService(IN nn::account::Uid _0, OUT nn::friends::detail::ipc::INotificationService * _1);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::friends::detail::ipc::IFriendService::AcceptFriendRequest(IN nn::account::Uid _0, IN nn::friends::RequestId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::AddFacedFriendRequest(IN nn::friends::FacedFriendRequestRegistrationKey _0, IN nn::account::Nickname _1, IN nn::account::Uid _2, IN uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::AddFacedFriendRequestForApplication(IN nn::friends::FacedFriendRequestRegistrationKey _0, IN nn::account::Nickname _1, IN nn::account::Uid _2, IN uint64_t _3, IN gpid _4, IN uint8_t * _5, guint _5_size, IN nn::friends::InAppScreenName * _6, guint _6_size, IN nn::friends::InAppScreenName * _7, guint _7_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 0, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(0x19, 1, temp8);
	ctu->cpu.readmem(temp7, temp9, temp8);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	delete[] temp9;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::AddPlayHistory(IN nn::account::Uid _0, IN uint64_t _1, IN gpid _2, IN nn::friends::PlayHistoryRegistrationKey * _3, guint _3_size, IN nn::friends::InAppScreenName * _4, guint _4_size, IN nn::friends::InAppScreenName * _5, guint _5_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(0x19, 2, temp8);
	ctu->cpu.readmem(temp7, temp9, temp8);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	delete[] temp9;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::BlockUser(IN int32_t _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::BlockUserWithApplicationInfo(IN int32_t _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2, IN nn::friends::ApplicationInfo _3, IN nn::friends::InAppScreenName * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::Cancel() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::CancelFacedFriendRequest(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::CancelFriendRequest(IN nn::account::Uid _0, IN nn::friends::RequestId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::ChangeFriendFavoriteFlag(IN bool _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::ChangeFriendOnlineNotificationFlag(IN bool _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::ChangeFriendRequestReception(IN bool _0, IN nn::account::Uid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::ChangePlayLogPermission(IN int32_t _0, IN nn::account::Uid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::ChangePresencePermission(IN int32_t _0, IN nn::account::Uid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::ClearPlayLog(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::DeclareCloseOnlinePlaySession(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::DeclareOpenOnlinePlaySession(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::DeleteFriend(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::DeleteNetworkServiceAccountCache(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::DeletePlayHistory(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::DropFriendNewlyFlag(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::DropFriendNewlyFlags(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetBlockedUserList(IN int32_t _0, IN nn::account::Uid _1, OUT int32_t& _2, OUT nn::friends::detail::BlockedUserImpl * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetBlockedUserListIds(IN int32_t _0, IN nn::account::Uid _1, OUT int32_t& _2, OUT nn::account::NetworkServiceAccountId * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetCompletionEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetExternalApplicationCatalog(IN nn::settings::LanguageCode _0, IN nn::friends::ExternalApplicationCatalogId _1, OUT nn::friends::ExternalApplicationCatalog * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetFacedFriendRequestProfileImage(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, OUT int32_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetFacedFriendRequestProfileImageFromPath(IN int8_t * _0, guint _0_size, OUT int32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetFacedFriendRequestRegistrationKey(IN nn::account::Uid _0, OUT nn::friends::FacedFriendRequestRegistrationKey& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::friends::FacedFriendRequestRegistrationKey>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetFriendCandidateList(IN int32_t _0, IN nn::account::Uid _1, OUT int32_t& _2, OUT nn::friends::detail::FriendCandidateImpl * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetFriendCount(IN nn::account::Uid _0, IN nn::friends::detail::ipc::SizedFriendFilter _1, IN uint64_t _2, IN gpid _3, OUT int32_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetFriendDetailedInfo(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, OUT nn::friends::detail::FriendDetailedInfoImpl * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetFriendList(IN int32_t _0, IN nn::account::Uid _1, IN nn::friends::detail::ipc::SizedFriendFilter _2, IN uint64_t _3, IN gpid _4, OUT int32_t& _5, OUT nn::friends::detail::FriendImpl * _6, guint _6_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetFriendListIds(IN int32_t _0, IN nn::account::Uid _1, IN nn::friends::detail::ipc::SizedFriendFilter _2, IN uint64_t _3, IN gpid _4, OUT int32_t& _5, OUT nn::account::NetworkServiceAccountId * _6, guint _6_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetFriendProfileImage(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, OUT int32_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetFriendRequestList(IN int32_t _0, IN int32_t _1, IN nn::account::Uid _2, OUT int32_t& _3, OUT nn::friends::detail::FriendRequestImpl * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetNewlyFriendCount(IN nn::account::Uid _0, OUT int32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetNintendoNetworkIdInfo(IN int32_t _0, IN nn::account::Uid _1, OUT int32_t& _2, OUT nn::friends::NintendoNetworkIdUserInfo * _3, guint _3_size, OUT nn::friends::detail::NintendoNetworkIdFriendImpl * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetPlayHistoryList(IN int32_t _0, IN nn::account::Uid _1, OUT int32_t& _2, OUT nn::friends::detail::PlayHistoryImpl * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetPlayHistoryRegistrationKey(IN bool _0, IN nn::account::Uid _1, OUT nn::friends::PlayHistoryRegistrationKey * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetPlayHistoryRegistrationKeyWithNetworkServiceAccountId(IN bool _0, IN nn::account::NetworkServiceAccountId _1, OUT nn::friends::PlayHistoryRegistrationKey * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetPlayHistoryStatistics(IN nn::account::Uid _0, OUT nn::friends::PlayHistoryStatistics& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetProfileExtraFromFriendCode(IN nn::friends::FriendCode _0, IN nn::account::Uid _1, OUT nn::friends::detail::ProfileExtraImpl * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetProfileExtraList(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId * _1, guint _1_size, OUT nn::friends::detail::ProfileExtraImpl * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetProfileImageUrl(IN nn::friends::Url _0, IN int32_t _1, OUT nn::friends::Url& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::friends::Url>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetProfileList(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId * _1, guint _1_size, OUT nn::friends::detail::ProfileImpl * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetReceivedFriendRequestCount(IN nn::account::Uid _0, OUT int32_t& _1, OUT int32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetRelationship(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, OUT nn::friends::Relationship& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::GetUserPresenceView(IN nn::account::Uid _0, OUT nn::friends::detail::UserPresenceViewImpl * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::IssueFriendCode(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::LoadFriendSetting(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, OUT nn::friends::detail::FriendSettingImpl * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::LoadUserSetting(IN nn::account::Uid _0, OUT nn::friends::detail::UserSettingImpl * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::ReadFriendRequest(IN nn::account::Uid _0, IN nn::friends::RequestId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::RejectFriendRequest(IN nn::account::Uid _0, IN nn::friends::RequestId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::RequestListSummaryOverlayNotification() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::RequestSyncFriendList(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::ResendFacedFriendRequest(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::SendFriendRequest(IN int32_t _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::SendFriendRequestForApplication(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1, IN uint64_t _2, IN gpid _3, IN nn::friends::InAppScreenName * _4, guint _4_size, IN nn::friends::InAppScreenName * _5, guint _5_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::SendFriendRequestWithApplicationInfo(IN int32_t _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2, IN nn::friends::ApplicationInfo _3, IN nn::friends::InAppScreenName * _4, guint _4_size, IN nn::friends::InAppScreenName * _5, guint _5_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::SendFriendRequestWithExternalApplicationCatalogId(IN int32_t _0, IN nn::account::Uid _1, IN nn::account::NetworkServiceAccountId _2, IN nn::friends::ExternalApplicationCatalogId _3, IN nn::friends::InAppScreenName * _4, guint _4_size, IN nn::friends::InAppScreenName * _5, guint _5_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::SendFriendRequestWithNintendoNetworkIdInfo(IN nn::friends::MiiName _0, IN nn::friends::MiiImageUrlParam _1, IN nn::friends::MiiName _2, IN nn::friends::MiiImageUrlParam _3, IN int32_t _4, IN nn::account::Uid _5, IN nn::account::NetworkServiceAccountId _6) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::SyncBlockedUserList(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::SyncFriendList(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::SyncUserSetting(IN nn::account::Uid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::UnblockUser(IN nn::account::Uid _0, IN nn::account::NetworkServiceAccountId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::UpdateFriendInfo(IN nn::account::Uid _0, IN uint64_t _1, IN gpid _2, IN nn::account::NetworkServiceAccountId * _3, guint _3_size, OUT nn::friends::detail::FriendImpl * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::friends::detail::ipc::IFriendService::UpdateUserPresence(IN nn::account::Uid _0, IN uint64_t _1, IN gpid _2, IN nn::friends::detail::UserPresenceImpl * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::friends::detail::ipc::INotificationService::Clear() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::INotificationService::GetEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::friends::detail::ipc::INotificationService::Pop(OUT nn::friends::detail::ipc::SizedNotificationInfo& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::friends::detail::ipc::IServiceCreator::CreateFriendService(OUT nn::friends::detail::ipc::IFriendService * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::friends::detail::ipc::IFriendService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::friends::detail::ipc::IServiceCreator::CreateNotificationService(IN nn::account::Uid _0, OUT nn::friends::detail::ipc::INotificationService * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::friends::detail::ipc::INotificationService(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::fssrv::sf {
	class IDeviceOperator {
	public:
		IDeviceOperator();
		uint32_t EraseAndWriteParamDirectly(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t EraseGameCard(IN uint32_t _0, IN uint64_t _1);
		uint32_t EraseMmc(IN uint32_t _0);
		uint32_t FinalizeGameCardDriver();
		uint32_t ForceEraseGameCard();
		uint32_t GetAndClearMmcErrorInfo(IN uint64_t _0, OUT uint128_t& _1, OUT uint64_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t GetAndClearSdCardErrorInfo(IN uint64_t _0, OUT uint128_t& _1, OUT uint64_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t GetGameCardAsicInfo(IN uint64_t _0, IN uint64_t _1, IN uint8_t * _2, guint _2_size, OUT uint8_t * _3, guint _3_size);
		uint32_t GetGameCardAttribute(IN uint32_t _0, OUT uint8_t& attribute);
		uint32_t GetGameCardCid(IN uint64_t _0, OUT uint8_t * cid, guint cid_size);
		uint32_t GetGameCardDeviceCertificate(IN uint64_t _0, IN uint32_t _1, OUT uint8_t * certificate, guint certificate_size);
		uint32_t GetGameCardDeviceId(IN uint64_t _0, OUT uint8_t * deviceID, guint deviceID_size);
		uint32_t GetGameCardDeviceIdForProdCard(IN uint64_t _0, IN uint64_t _1, IN uint8_t * _2, guint _2_size, OUT uint8_t * errorInfo, guint errorInfo_size);
		uint32_t GetGameCardErrorInfo(OUT uint128_t& errorInfo);
		uint32_t GetGameCardErrorReportInfo(OUT uint8_t * errorReportInfo);
		uint32_t GetGameCardHandle(OUT uint32_t& gamecardHandle);
		uint32_t GetGameCardIdSet(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetGameCardImageHash(IN uint64_t _0, IN uint32_t _1, OUT uint8_t * imageHash, guint imageHash_size);
		uint32_t GetGameCardUpdatePartitionInfo(IN uint32_t _0, OUT uint32_t& version, OUT nn::ApplicationId& TID);
		uint32_t GetMmcCid(IN uint64_t _0, OUT uint8_t * cid, guint cid_size);
		uint32_t GetMmcExtendedCsd(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetMmcPartitionSize(IN uint32_t _0, OUT uint64_t& paritionSize);
		uint32_t GetMmcPatrolCount(OUT uint32_t& patrolCount);
		uint32_t GetMmcSpeedMode(OUT uint64_t& speedMode);
		uint32_t GetSdCardCid(IN uint64_t _0, OUT uint8_t * cid, guint cid_size);
		uint32_t GetSdCardProtectedAreaSize(OUT uint64_t& protectedSize);
		uint32_t GetSdCardSpeedMode(OUT uint64_t& sdSpeed);
		uint32_t GetSdCardUserAreaSize(OUT uint64_t& size);
		uint32_t GetSpeedEmulationMode(OUT uint32_t& emuMode);
		uint32_t IsGameCardInserted(OUT uint8_t& isGameInserted);
		uint32_t IsSdCardInserted(OUT uint8_t& isSdInserted);
		uint32_t SetSpeedEmulationMode(IN uint32_t mode);
		uint32_t SetVerifyWriteEnalbleFlag(IN uint8_t flag);
		uint32_t WriteToGameCard(IN uint64_t _0, IN uint64_t _1, OUT uint8_t * _2, guint _2_size);
	};
	class IDirectory {
	public:
		IDirectory();
		uint32_t GetEntryCount(OUT uint64_t& _0);
		uint32_t Read(OUT uint64_t& _0, OUT uint8_t * _1, guint _1_size);
	};
	class IEventNotifier {
	public:
		IEventNotifier();
		uint32_t Unknown0(OUT KObject * _0);
	};
	class IFile {
	public:
		IFile();
		uint32_t Flush();
		uint32_t GetSize(OUT uint64_t& fileSize);
		uint32_t Read(IN uint64_t _0, IN uint64_t offset, IN uint32_t size, OUT uint64_t& out_size, OUT int8_t * out_buf, guint out_buf_size);
		uint32_t SetSize(IN uint64_t size);
		uint32_t Write(IN uint64_t _0, IN uint64_t offset, IN uint32_t size, IN int8_t * buf, guint buf_size);
	};
	class IFileSystem {
	public:
		IFileSystem();
		uint32_t CleanDirectoryRecursively(IN int8_t * path, guint path_size);
		uint32_t Commit();
		uint32_t CreateDirectory(IN int8_t * path, guint path_size);
		uint32_t CreateFile(IN uint64_t mode, IN uint32_t size, IN int8_t * path, guint path_size);
		uint32_t DeleteDirectory(IN int8_t * path, guint path_size);
		uint32_t DeleteDirectoryRecursively(IN int8_t * path, guint path_size);
		uint32_t DeleteFile(IN int8_t * path, guint path_size);
		uint32_t GetEntryType(IN int8_t * path, guint path_size, OUT uint32_t& _1);
		uint32_t GetFileTimeStampRaw(IN int8_t * path, guint path_size, OUT uint8_t * timestamp);
		uint32_t GetFreeSpaceSize(IN int8_t * path, guint path_size, OUT uint64_t& totalFreeSpace);
		uint32_t GetTotalSpaceSize(IN int8_t * path, guint path_size, OUT uint64_t& totalSize);
		uint32_t OpenDirectory(IN uint32_t _0, IN int8_t * path, guint path_size, OUT nn::fssrv::sf::IDirectory * directory);
		uint32_t OpenFile(IN uint32_t mode, IN int8_t * path, guint path_size, OUT nn::fssrv::sf::IFile * file);
		uint32_t RenameDirectory(IN int8_t * oldPath, guint oldPath_size, IN int8_t * newPath, guint newPath_size);
		uint32_t RenameFile(IN int8_t * oldPath, guint oldPath_size, IN int8_t * newPath, guint newPath_size);
	};
	class IFileSystemProxy {
	public:
		IFileSystemProxy();
		uint32_t CorruptSaveDataForDebug(IN nn::ApplicationId tid);
		uint32_t CreatePaddingFile(IN uint64_t size);
		uint32_t CreateSaveData(IN nn::fssrv::sf::SaveStruct saveStruct, IN nn::fssrv::sf::SaveCreateStruct saveCreate, IN uint128_t input);
		uint32_t CreateSystemSaveData(IN nn::fssrv::sf::SaveStruct saveStruct, IN nn::fssrv::sf::SaveCreateStruct saveCreate);
		uint32_t DeleteAllPaddingFiles();
		uint32_t DeleteSaveData(IN nn::ApplicationId tid);
		uint32_t DeleteSaveDataWithSpaceId(IN uint8_t _0, IN uint64_t _1);
		uint32_t DisableAutoSaveDataCreation();
		uint32_t ExtendSaveData(IN uint8_t _0, IN uint64_t _1, IN uint64_t _2, IN uint64_t _3);
		uint32_t FormatSdCard();
		uint32_t FormatSdCardDryRun();
		uint32_t GetAndClearFileSystemProxyErrorInfo(OUT uint8_t * errorInfo);
		uint32_t GetGlobalAccessLogMode(OUT uint32_t& logMode);
		uint32_t GetRightsId(IN uint64_t _0, IN uint8_t _1, OUT uint128_t& rights);
		uint32_t GetRightsIdByPath(IN int8_t * path, guint path_size, OUT uint128_t& rights);
		uint32_t GetRightsIdByPath2(IN int8_t * path, guint path_size, OUT uint128_t& rights, OUT uint8_t& _2);
		uint32_t Initialize(IN uint64_t _0, IN gpid _1);
		uint32_t InvalidateBisCache();
		uint32_t IsExFatSupported(OUT uint8_t& isSupported);
		uint32_t MountBis(IN nn::fssrv::sf::Partition partitionID, IN int8_t * path, guint path_size, OUT nn::fssrv::sf::IFileSystem * Bis);
		uint32_t MountContent(IN nn::ApplicationId tid, IN uint32_t flag, IN int8_t * path, guint path_size, OUT nn::fssrv::sf::IFileSystem * contentFs);
		uint32_t MountContent7(IN nn::ApplicationId tid, IN uint32_t ncaType, OUT nn::fssrv::sf::IFileSystem * _2);
		uint32_t MountContentStorage(IN uint32_t contentStorageID, OUT nn::fssrv::sf::IFileSystem * contentFs);
		uint32_t MountGameCardPartition(IN uint32_t _0, IN uint32_t _1, OUT nn::fssrv::sf::IFileSystem * gameCardPartitionFs);
		uint32_t MountImageDirectory(IN uint32_t _0, OUT nn::fssrv::sf::IFileSystem * imageFs);
		uint32_t MountSaveData(IN uint8_t input, IN nn::fssrv::sf::SaveStruct saveStruct, OUT nn::fssrv::sf::IFileSystem * saveDataFs);
		uint32_t MountSaveDataReadOnly(IN uint8_t input, IN nn::fssrv::sf::SaveStruct saveStruct, OUT nn::fssrv::sf::IFileSystem * saveDataFs);
		uint32_t MountSdCard(OUT nn::fssrv::sf::IFileSystem * sdCard);
		uint32_t MountSystemSaveData(IN uint8_t input, IN nn::fssrv::sf::SaveStruct saveStruct, OUT nn::fssrv::sf::IFileSystem * systemSaveDataFs);
		uint32_t OpenBisPartition(IN nn::fssrv::sf::Partition partitionID, OUT nn::fssrv::sf::IStorage * BisPartition);
		uint32_t OpenDataFileSystemByApplicationId(IN nn::ApplicationId tid, OUT nn::fssrv::sf::IFileSystem * dataFiles);
		uint32_t OpenDataFileSystemByCurrentProcess(OUT nn::fssrv::sf::IFileSystem * _0);
		uint32_t OpenDataStorageByApplicationId(IN nn::ApplicationId tid, OUT nn::fssrv::sf::IStorage * dataStorage);
		uint32_t OpenDataStorageByCurrentProcess(OUT nn::fssrv::sf::IStorage * dataStorage);
		uint32_t OpenDataStorageByDataId(IN nn::ApplicationId tid, IN uint8_t storageId, OUT nn::fssrv::sf::IStorage * dataStorage);
		uint32_t OpenDeviceOperator(OUT nn::fssrv::sf::IDeviceOperator * _0);
		uint32_t OpenGameCardDetectionEventNotifier(OUT nn::fssrv::sf::IEventNotifier * GameCardEventNotify);
		uint32_t OpenGameCardPartition(IN nn::fssrv::sf::Partition partitionID, IN uint32_t _1, OUT nn::fssrv::sf::IStorage * gameCardFs);
		uint32_t OpenHostFileSystemImpl(IN int8_t * path, guint path_size, OUT nn::fssrv::sf::IFileSystem * _1);
		uint32_t OpenRomStorage(OUT nn::fssrv::sf::IStorage * _0);
		uint32_t OpenSaveDataInfoReader(OUT nn::fssrv::sf::ISaveDataInfoReader * _0);
		uint32_t OpenSaveDataIterator(IN uint8_t _0, OUT IUnknown * _1);
		uint32_t OpenSaveDataThumbnailFile(IN uint8_t _0, IN uint8_t * _1, IN uint32_t _2, OUT nn::fssrv::sf::IFile * thumbnail);
		uint32_t OpenSdCardDetectionEventNotifier(OUT nn::fssrv::sf::IEventNotifier * SdEventNotify);
		uint32_t OutputAccessLogToSdCard(IN void * logText, guint logText_size);
		uint32_t QuerySaveDataTotalSize(IN uint64_t _0, IN uint64_t _1, OUT uint64_t& saveDataSize);
		uint32_t ReadSaveDataFileSystemExtraData(IN uint64_t _0, OUT void * _1, guint _1_size);
		uint32_t ReadSaveDataFileSystemExtraDataWithSpaceId(IN uint8_t _0, IN uint64_t _1, OUT void * _2, guint _2_size);
		uint32_t RegisterExternalKey(IN uint128_t _0, IN uint128_t _1);
		uint32_t RegisterSaveDataAtomicDeletion(IN void * _0, guint _0_size);
		uint32_t SetBisRootForHost(IN uint32_t _0, IN int8_t * path, guint path_size);
		uint32_t SetCurrentPosixTime(IN uint64_t time);
		uint32_t SetGlobalAccessLogMode(IN uint32_t mode);
		uint32_t SetSaveDataRootPath(IN int8_t * path, guint path_size);
		uint32_t SetSaveDataSize(IN uint64_t _0, IN uint64_t _1);
		uint32_t SetSdCardEncryptionSeed(IN uint128_t seedmaybe);
		uint32_t UnregisterExternalKey();
		uint32_t VerifySaveData(IN nn::ApplicationId tid, OUT void * _1, guint _1_size);
		uint32_t WriteSaveDataFileSystemExtraData(IN uint64_t _0, IN uint8_t _1, IN void * _2, guint _2_size);
	};
	class IFileSystemProxyForLoader {
	public:
		IFileSystemProxyForLoader();
		uint32_t IsCodeMounted(IN nn::ApplicationId TID, OUT uint8_t& isMounted);
		uint32_t MountCode(IN nn::ApplicationId TID, IN int8_t * contentPath, guint contentPath_size, OUT nn::fssrv::sf::IFileSystem * contentFs);
	};
	class IProgramRegistry {
	public:
		IProgramRegistry();
		uint32_t ClearFsPermissions(IN uint64_t pid);
		uint32_t SetEnabledProgramVerification(IN uint8_t enabled);
		uint32_t SetFsPermissions(IN uint64_t _0, IN uint64_t _1, IN uint8_t _2, IN uint64_t _3, IN uint64_t _4, IN uint8_t * _5, guint _5_size, IN uint8_t * _6, guint _6_size);
	};
	class ISaveDataInfoReader {
	public:
		ISaveDataInfoReader();
		uint32_t Unknown0(OUT uint64_t& _0, OUT uint8_t * _1, guint _1_size);
	};
	class IStorage {
	public:
		IStorage();
		uint32_t Flush();
		uint32_t GetSize(OUT uint64_t& size);
		uint32_t Read(IN uint64_t offset, IN uint64_t length, OUT int8_t * buffer, guint buffer_size);
		uint32_t SetSize(IN uint64_t size);
		uint32_t Write(IN uint64_t offset, IN uint64_t length, IN int8_t * data, guint data_size);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::fssrv::sf::IDeviceOperator::EraseAndWriteParamDirectly(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::EraseGameCard(IN uint32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::EraseMmc(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::FinalizeGameCardDriver() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::ForceEraseGameCard() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetAndClearMmcErrorInfo(IN uint64_t _0, OUT uint128_t& _1, OUT uint64_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetAndClearSdCardErrorInfo(IN uint64_t _0, OUT uint128_t& _1, OUT uint64_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardAsicInfo(IN uint64_t _0, IN uint64_t _1, IN uint8_t * _2, guint _2_size, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardAttribute(IN uint32_t _0, OUT uint8_t& attribute) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardCid(IN uint64_t _0, OUT uint8_t * cid, guint cid_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardDeviceCertificate(IN uint64_t _0, IN uint32_t _1, OUT uint8_t * certificate, guint certificate_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardDeviceId(IN uint64_t _0, OUT uint8_t * deviceID, guint deviceID_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardDeviceIdForProdCard(IN uint64_t _0, IN uint64_t _1, IN uint8_t * _2, guint _2_size, OUT uint8_t * errorInfo, guint errorInfo_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardErrorInfo(OUT uint128_t& errorInfo) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardErrorReportInfo(OUT uint8_t * errorReportInfo) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardHandle(OUT uint32_t& gamecardHandle) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardIdSet(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardImageHash(IN uint64_t _0, IN uint32_t _1, OUT uint8_t * imageHash, guint imageHash_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetGameCardUpdatePartitionInfo(IN uint32_t _0, OUT uint32_t& version, OUT nn::ApplicationId& TID) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetMmcCid(IN uint64_t _0, OUT uint8_t * cid, guint cid_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetMmcExtendedCsd(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetMmcPartitionSize(IN uint32_t _0, OUT uint64_t& paritionSize) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetMmcPatrolCount(OUT uint32_t& patrolCount) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetMmcSpeedMode(OUT uint64_t& speedMode) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetSdCardCid(IN uint64_t _0, OUT uint8_t * cid, guint cid_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetSdCardProtectedAreaSize(OUT uint64_t& protectedSize) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetSdCardSpeedMode(OUT uint64_t& sdSpeed) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetSdCardUserAreaSize(OUT uint64_t& size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::GetSpeedEmulationMode(OUT uint32_t& emuMode) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::IsGameCardInserted(OUT uint8_t& isGameInserted) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::IsSdCardInserted(OUT uint8_t& isSdInserted) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::SetSpeedEmulationMode(IN uint32_t mode) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::SetVerifyWriteEnalbleFlag(IN uint8_t flag) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDeviceOperator::WriteToGameCard(IN uint64_t _0, IN uint64_t _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IDirectory::GetEntryCount(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IDirectory::Read(OUT uint64_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IEventNotifier::Unknown0(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::fssrv::sf::IFile::Flush() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFile::GetSize(OUT uint64_t& fileSize) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFile::Read(IN uint64_t _0, IN uint64_t offset, IN uint32_t size, OUT uint64_t& out_size, OUT int8_t * out_buf, guint out_buf_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x46, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFile::SetSize(IN uint64_t size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFile::Write(IN uint64_t _0, IN uint64_t offset, IN uint32_t size, IN int8_t * buf, guint buf_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x45, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::CleanDirectoryRecursively(IN int8_t * path, guint path_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::Commit() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::CreateDirectory(IN int8_t * path, guint path_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::CreateFile(IN uint64_t mode, IN uint32_t size, IN int8_t * path, guint path_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::DeleteDirectory(IN int8_t * path, guint path_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::DeleteDirectoryRecursively(IN int8_t * path, guint path_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::DeleteFile(IN int8_t * path, guint path_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::GetEntryType(IN int8_t * path, guint path_size, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::GetFileTimeStampRaw(IN int8_t * path, guint path_size, OUT uint8_t * timestamp) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto temp4 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::GetFreeSpaceSize(IN int8_t * path, guint path_size, OUT uint64_t& totalFreeSpace) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::GetTotalSpaceSize(IN int8_t * path, guint path_size, OUT uint64_t& totalSize) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::OpenDirectory(IN uint32_t _0, IN int8_t * path, guint path_size, OUT nn::fssrv::sf::IDirectory * directory) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	directory OMG = new nn::fssrv::sf::IDirectory(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::OpenFile(IN uint32_t mode, IN int8_t * path, guint path_size, OUT nn::fssrv::sf::IFile * file) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	file OMG = new nn::fssrv::sf::IFile(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::RenameDirectory(IN int8_t * oldPath, guint oldPath_size, IN int8_t * newPath, guint newPath_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystem::RenameFile(IN int8_t * oldPath, guint oldPath_size, IN int8_t * newPath, guint newPath_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::CorruptSaveDataForDebug(IN nn::ApplicationId tid) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::CreatePaddingFile(IN uint64_t size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::CreateSaveData(IN nn::fssrv::sf::SaveStruct saveStruct, IN nn::fssrv::sf::SaveCreateStruct saveCreate, IN uint128_t input) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::CreateSystemSaveData(IN nn::fssrv::sf::SaveStruct saveStruct, IN nn::fssrv::sf::SaveCreateStruct saveCreate) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::DeleteAllPaddingFiles() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::DeleteSaveData(IN nn::ApplicationId tid) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::DeleteSaveDataWithSpaceId(IN uint8_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::DisableAutoSaveDataCreation() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::ExtendSaveData(IN uint8_t _0, IN uint64_t _1, IN uint64_t _2, IN uint64_t _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::FormatSdCard() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::FormatSdCardDryRun() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::GetAndClearFileSystemProxyErrorInfo(OUT uint8_t * errorInfo) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::GetGlobalAccessLogMode(OUT uint32_t& logMode) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::GetRightsId(IN uint64_t _0, IN uint8_t _1, OUT uint128_t& rights) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::GetRightsIdByPath(IN int8_t * path, guint path_size, OUT uint128_t& rights) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::GetRightsIdByPath2(IN int8_t * path, guint path_size, OUT uint128_t& rights, OUT uint8_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::Initialize(IN uint64_t _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::InvalidateBisCache() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::IsExFatSupported(OUT uint8_t& isSupported) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::MountBis(IN nn::fssrv::sf::Partition partitionID, IN int8_t * path, guint path_size, OUT nn::fssrv::sf::IFileSystem * Bis) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	Bis OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::MountContent(IN nn::ApplicationId tid, IN uint32_t flag, IN int8_t * path, guint path_size, OUT nn::fssrv::sf::IFileSystem * contentFs) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	contentFs OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::MountContent7(IN nn::ApplicationId tid, IN uint32_t ncaType, OUT nn::fssrv::sf::IFileSystem * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::MountContentStorage(IN uint32_t contentStorageID, OUT nn::fssrv::sf::IFileSystem * contentFs) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	contentFs OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::MountGameCardPartition(IN uint32_t _0, IN uint32_t _1, OUT nn::fssrv::sf::IFileSystem * gameCardPartitionFs) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	gameCardPartitionFs OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::MountImageDirectory(IN uint32_t _0, OUT nn::fssrv::sf::IFileSystem * imageFs) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	imageFs OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::MountSaveData(IN uint8_t input, IN nn::fssrv::sf::SaveStruct saveStruct, OUT nn::fssrv::sf::IFileSystem * saveDataFs) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	saveDataFs OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::MountSaveDataReadOnly(IN uint8_t input, IN nn::fssrv::sf::SaveStruct saveStruct, OUT nn::fssrv::sf::IFileSystem * saveDataFs) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	saveDataFs OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::MountSdCard(OUT nn::fssrv::sf::IFileSystem * sdCard) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	sdCard OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::MountSystemSaveData(IN uint8_t input, IN nn::fssrv::sf::SaveStruct saveStruct, OUT nn::fssrv::sf::IFileSystem * systemSaveDataFs) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	systemSaveDataFs OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenBisPartition(IN nn::fssrv::sf::Partition partitionID, OUT nn::fssrv::sf::IStorage * BisPartition) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	BisPartition OMG = new nn::fssrv::sf::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenDataFileSystemByApplicationId(IN nn::ApplicationId tid, OUT nn::fssrv::sf::IFileSystem * dataFiles) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	dataFiles OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenDataFileSystemByCurrentProcess(OUT nn::fssrv::sf::IFileSystem * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenDataStorageByApplicationId(IN nn::ApplicationId tid, OUT nn::fssrv::sf::IStorage * dataStorage) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	dataStorage OMG = new nn::fssrv::sf::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenDataStorageByCurrentProcess(OUT nn::fssrv::sf::IStorage * dataStorage) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	dataStorage OMG = new nn::fssrv::sf::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenDataStorageByDataId(IN nn::ApplicationId tid, IN uint8_t storageId, OUT nn::fssrv::sf::IStorage * dataStorage) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	dataStorage OMG = new nn::fssrv::sf::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenDeviceOperator(OUT nn::fssrv::sf::IDeviceOperator * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::fssrv::sf::IDeviceOperator(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenGameCardDetectionEventNotifier(OUT nn::fssrv::sf::IEventNotifier * GameCardEventNotify) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	GameCardEventNotify OMG = new nn::fssrv::sf::IEventNotifier(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenGameCardPartition(IN nn::fssrv::sf::Partition partitionID, IN uint32_t _1, OUT nn::fssrv::sf::IStorage * gameCardFs) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	gameCardFs OMG = new nn::fssrv::sf::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenHostFileSystemImpl(IN int8_t * path, guint path_size, OUT nn::fssrv::sf::IFileSystem * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_1 OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenRomStorage(OUT nn::fssrv::sf::IStorage * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::fssrv::sf::IStorage(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenSaveDataInfoReader(OUT nn::fssrv::sf::ISaveDataInfoReader * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::fssrv::sf::ISaveDataInfoReader(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenSaveDataIterator(IN uint8_t _0, OUT IUnknown * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenSaveDataThumbnailFile(IN uint8_t _0, IN uint8_t * _1, IN uint32_t _2, OUT nn::fssrv::sf::IFile * thumbnail) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	thumbnail OMG = new nn::fssrv::sf::IFile(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OpenSdCardDetectionEventNotifier(OUT nn::fssrv::sf::IEventNotifier * SdEventNotify) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	SdEventNotify OMG = new nn::fssrv::sf::IEventNotifier(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::OutputAccessLogToSdCard(IN void * logText, guint logText_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::QuerySaveDataTotalSize(IN uint64_t _0, IN uint64_t _1, OUT uint64_t& saveDataSize) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::ReadSaveDataFileSystemExtraData(IN uint64_t _0, OUT void * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::ReadSaveDataFileSystemExtraDataWithSpaceId(IN uint8_t _0, IN uint64_t _1, OUT void * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::RegisterExternalKey(IN uint128_t _0, IN uint128_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::RegisterSaveDataAtomicDeletion(IN void * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::SetBisRootForHost(IN uint32_t _0, IN int8_t * path, guint path_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::SetCurrentPosixTime(IN uint64_t time) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::SetGlobalAccessLogMode(IN uint32_t mode) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::SetSaveDataRootPath(IN int8_t * path, guint path_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::SetSaveDataSize(IN uint64_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::SetSdCardEncryptionSeed(IN uint128_t seedmaybe) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::UnregisterExternalKey() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::VerifySaveData(IN nn::ApplicationId tid, OUT void * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxy::WriteSaveDataFileSystemExtraData(IN uint64_t _0, IN uint8_t _1, IN void * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxyForLoader::IsCodeMounted(IN nn::ApplicationId TID, OUT uint8_t& isMounted) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IFileSystemProxyForLoader::MountCode(IN nn::ApplicationId TID, IN int8_t * contentPath, guint contentPath_size, OUT nn::fssrv::sf::IFileSystem * contentFs) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	contentFs OMG = new nn::fssrv::sf::IFileSystem(resp.move_handles[0]);
	return ret;
}
uint32_t nn::fssrv::sf::IProgramRegistry::ClearFsPermissions(IN uint64_t pid) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IProgramRegistry::SetEnabledProgramVerification(IN uint8_t enabled) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IProgramRegistry::SetFsPermissions(IN uint64_t _0, IN uint64_t _1, IN uint8_t _2, IN uint64_t _3, IN uint64_t _4, IN uint8_t * _5, guint _5_size, IN uint8_t * _6, guint _6_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(5, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::fssrv::sf::ISaveDataInfoReader::Unknown0(OUT uint64_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IStorage::Flush() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IStorage::GetSize(OUT uint64_t& size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IStorage::Read(IN uint64_t offset, IN uint64_t length, OUT int8_t * buffer, guint buffer_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x46, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::fssrv::sf::IStorage::SetSize(IN uint64_t size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::fssrv::sf::IStorage::Write(IN uint64_t offset, IN uint64_t length, IN int8_t * data, guint data_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x45, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::gpio {
	class IManager {
	public:
		IManager();
		uint32_t GetPadSession(IN uint32_t _0, OUT nn::gpio::IPadSession * _1);
		uint32_t Unknown0(IN uint32_t _0, OUT IUnknown * _1);
		uint32_t Unknown2(IN uint32_t _0, OUT IUnknown * _1);
		uint32_t Unknown3(IN uint32_t _0, OUT uint8_t& _1);
		uint32_t Unknown4(OUT uint128_t& _0);
		uint32_t Unknown5(IN uint32_t _0, IN uint8_t _1);
		uint32_t Unknown6(IN uint8_t _0);
	};
	class IPadSession {
	public:
		IPadSession();
		uint32_t Unknown0(IN uint32_t _0);
		uint32_t Unknown1(OUT uint32_t& _0);
		uint32_t Unknown10(OUT KObject * _0);
		uint32_t Unknown11();
		uint32_t Unknown12(IN uint8_t _0);
		uint32_t Unknown13(OUT uint8_t& _0);
		uint32_t Unknown14(IN uint32_t _0);
		uint32_t Unknown15(OUT uint32_t& _0);
		uint32_t Unknown2(IN uint32_t _0);
		uint32_t Unknown3(OUT uint32_t& _0);
		uint32_t Unknown4(IN uint8_t _0);
		uint32_t Unknown5(OUT uint8_t& _0);
		uint32_t Unknown6(OUT uint32_t& _0);
		uint32_t Unknown7();
		uint32_t Unknown8(IN uint32_t _0);
		uint32_t Unknown9(OUT uint32_t& _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::gpio::IManager::GetPadSession(IN uint32_t _0, OUT nn::gpio::IPadSession * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::gpio::IPadSession(resp.move_handles[0]);
	return ret;
}
uint32_t nn::gpio::IManager::Unknown0(IN uint32_t _0, OUT IUnknown * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::gpio::IManager::Unknown2(IN uint32_t _0, OUT IUnknown * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::gpio::IManager::Unknown3(IN uint32_t _0, OUT uint8_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IManager::Unknown4(OUT uint128_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IManager::Unknown5(IN uint32_t _0, IN uint8_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IManager::Unknown6(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown0(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown1(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown10(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown12(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown13(OUT uint8_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown14(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown15(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown2(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown3(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown4(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown5(OUT uint8_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown6(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown8(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::gpio::IPadSession::Unknown9(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::hid {
	class IActiveVibrationDeviceList {
	public:
		IActiveVibrationDeviceList();
		uint32_t ActivateVibrationDevice(IN nn::hid::VibrationDeviceHandle _0);
	};
	class IAppletResource {
	public:
		IAppletResource();
		uint32_t GetSharedMemoryHandle(OUT KObject * _0);
	};
	class IHidDebugServer {
	public:
		IHidDebugServer();
		uint32_t ActivateFirmwareUpdate();
		uint32_t DeactivateCaptureButton();
		uint32_t DeactivateConsoleSixAxisSensor();
		uint32_t DeactivateDebugPad();
		uint32_t DeactivateFirmwareUpdate();
		uint32_t DeactivateGesture();
		uint32_t DeactivateHomeButton();
		uint32_t DeactivateInputDetector();
		uint32_t DeactivateJoyXpad(IN nn::hid::JoyXpadId _0);
		uint32_t DeactivateKeyboard();
		uint32_t DeactivateMouse();
		uint32_t DeactivateSleepButton();
		uint32_t DeactivateTouchScreen();
		uint32_t DeactivateXpad(IN nn::hid::BasicXpadId _0);
		uint32_t DiscardFirmwareInfoCacheForRevert();
		uint32_t GetAvailableFirmwareVersionForRevert(IN nn::hid::system::UniquePadId _0, OUT nn::hid::system::FirmwareVersion& _1);
		uint32_t GetDestinationFirmwareVersion(IN uint32_t _0, IN nn::hid::system::DeviceType _1, OUT nn::hid::system::FirmwareVersion& _2);
		uint32_t GetFirmwareUpdateStage(OUT int64_t& _0, OUT int64_t& _1);
		uint32_t GetFirmwareVersion(IN uint32_t _0, IN nn::hid::system::DeviceType _1, OUT nn::hid::system::FirmwareVersion& _2);
		uint32_t GetShiftAccelerometerCalibrationValue(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT float32_t& _3, OUT float32_t& _4);
		uint32_t GetShiftGyroscopeCalibrationValue(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT float32_t& _3, OUT float32_t& _4);
		uint32_t SetCaptureButtonAutoPilotState(IN nn::hid::debug::CaptureButtonAutoPilotState _0);
		uint32_t SetDebugPadAutoPilotState(IN nn::hid::debug::DebugPadAutoPilotState _0);
		uint32_t SetHomeButtonAutoPilotState(IN nn::hid::debug::HomeButtonAutoPilotState _0);
		uint32_t SetKeyboardAutoPilotState(IN nn::hid::debug::KeyboardAutoPilotState _0);
		uint32_t SetMouseAutoPilotState(IN nn::hid::debug::MouseAutoPilotState _0);
		uint32_t SetShiftAccelerometerCalibrationValue(IN nn::hid::SixAxisSensorHandle _0, IN float32_t _1, IN float32_t _2, IN nn::applet::AppletResourceUserId _3, IN gpid _4);
		uint32_t SetShiftGyroscopeCalibrationValue(IN nn::hid::SixAxisSensorHandle _0, IN float32_t _1, IN float32_t _2, IN nn::applet::AppletResourceUserId _3, IN gpid _4);
		uint32_t SetSleepButtonAutoPilotState(IN nn::hid::debug::SleepButtonAutoPilotState _0);
		uint32_t SetTouchScreenAutoPilotState(IN nn::hid::TouchState * _0, guint _0_size);
		uint32_t SetXpadAutoPilotState(IN nn::hid::BasicXpadId _0, IN nn::hid::debug::BasicXpadAutoPilotState _1);
		uint32_t StartFirmwareUpdate(IN nn::hid::system::UniquePadId _0);
		uint32_t StartFirmwareUpdateForRevert(IN nn::hid::system::UniquePadId _0);
		uint32_t UnsetCaptureButtonAutoPilotState();
		uint32_t UnsetDebugPadAutoPilotState();
		uint32_t UnsetHomeButtonAutoPilotState();
		uint32_t UnsetKeyboardAutoPilotState();
		uint32_t UnsetMouseAutoPilotState();
		uint32_t UnsetSleepButtonAutoPilotState();
		uint32_t UnsetTouchScreenAutoPilotState();
		uint32_t UnsetXpadAutoPilotState(IN nn::hid::BasicXpadId _0);
		uint32_t UpdateControllerColor(IN nn::util::Unorm8x4 _0, IN nn::util::Unorm8x4 _1, IN nn::hid::system::UniquePadId _2);
	};
	class IHidServer {
	public:
		IHidServer();
		uint32_t AcquireNpadStyleSetUpdateEventHandle(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN uint64_t _2, IN gpid _3, OUT KObject * _4);
		uint32_t AcquireXpadIdEventHandle(IN uint64_t _0, OUT KObject * _1);
		uint32_t ActivateConsoleSixAxisSensor(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t ActivateDebugPad(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t ActivateGesture(IN int32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t ActivateJoySixAxisSensor(IN nn::hid::JoyXpadId _0);
		uint32_t ActivateJoyXpad(IN nn::hid::JoyXpadId _0);
		uint32_t ActivateKeyboard(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t ActivateMouse(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t ActivateNpad(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t ActivateSixAxisSensor(IN nn::hid::BasicXpadId _0);
		uint32_t ActivateTouchScreen(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t ActivateXpad(IN nn::hid::BasicXpadId _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t CreateActiveVibrationDeviceList(OUT nn::hid::IActiveVibrationDeviceList * _0);
		uint32_t CreateAppletResource(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT nn::hid::IAppletResource * _2);
		uint32_t DeactivateJoySixAxisSensor(IN nn::hid::JoyXpadId _0);
		uint32_t DeactivateNpad(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t DeactivateSixAxisSensor(IN nn::hid::BasicXpadId _0);
		uint32_t DisconnectNpad(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t EnableSixAxisSensorFusion(IN bool _0, IN nn::hid::SixAxisSensorHandle _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t EnableUnintendedHomeButtonInputProtection(IN bool _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t EnableUsbFullKeyController(IN bool _0);
		uint32_t GetAccelerometerParameters(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT float32_t& _3, OUT float32_t& _4);
		uint32_t GetAccelerometerPlayMode(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT uint32_t& _3);
		uint32_t GetActualVibrationValue(IN nn::hid::VibrationDeviceHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT nn::hid::VibrationValue& _3);
		uint32_t GetGyroscopeZeroDriftMode(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT uint32_t& _3);
		uint32_t GetJoySixAxisSensorLifoHandle(IN nn::hid::JoyXpadId _0, OUT KObject * _1);
		uint32_t GetJoyXpadIds(OUT int64_t& _0, OUT nn::hid::JoyXpadId * _1, guint _1_size);
		uint32_t GetJoyXpadLifoHandle(IN nn::hid::JoyXpadId _0, OUT KObject * _1);
		uint32_t GetNpadCommunicationMode(OUT int64_t& _0);
		uint32_t GetNpadHandheldActivationMode(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT int64_t& _2);
		uint32_t GetNpadJoyHoldType(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT int64_t& _2);
		uint32_t GetPlayerLedPattern(IN uint32_t _0, OUT uint64_t& _1);
		uint32_t GetSixAxisSensorFusionParameters(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT float32_t& _3, OUT float32_t& _4);
		uint32_t GetSixAxisSensorLifoHandle(IN nn::hid::BasicXpadId _0, OUT KObject * _1);
		uint32_t GetSupportedNpadStyleSet(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT nn::hid::NpadStyleTag& _2);
		uint32_t GetVibrationDeviceInfo(IN nn::hid::VibrationDeviceHandle _0, OUT nn::hid::VibrationDeviceInfoForIpc& _1);
		uint32_t GetXpadIds(OUT int64_t& _0, OUT nn::hid::BasicXpadId * _1, guint _1_size);
		uint32_t IsSixAxisSensorAtRest(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT bool& _3);
		uint32_t IsSixAxisSensorFusionEnabled(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT bool& _3);
		uint32_t IsUnintendedHomeButtonInputProtectionEnabled(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT bool& _3);
		uint32_t IsUsbFullKeyControllerConnected(IN uint32_t _0, OUT bool& _1);
		uint32_t IsUsbFullKeyControllerEnabled(OUT bool& _0);
		uint32_t IsVibrationPermitted(OUT bool& _0);
		uint32_t MergeSingleJoyAsDualJoy(IN uint32_t _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t PermitVibration(IN bool _0);
		uint32_t ReleaseXpadIdEventHandle(IN uint64_t _0);
		uint32_t ResetAccelerometerParameters(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t ResetAccelerometerPlayMode(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t ResetGyroscopeZeroDriftMode(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t ResetSixAxisSensorFusionParameters(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t SendVibrationValue(IN nn::hid::VibrationDeviceHandle _0, IN nn::hid::VibrationValue _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t SendVibrationValues(IN nn::applet::AppletResourceUserId _0, IN nn::hid::VibrationDeviceHandle * _1, guint _1_size, IN nn::hid::VibrationValue * _2, guint _2_size);
		uint32_t SetAccelerometerParameters(IN nn::hid::SixAxisSensorHandle _0, IN float32_t _1, IN float32_t _2, IN nn::applet::AppletResourceUserId _3, IN gpid _4);
		uint32_t SetAccelerometerPlayMode(IN nn::hid::SixAxisSensorHandle _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t SetGyroscopeZeroDriftMode(IN nn::hid::SixAxisSensorHandle _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t SetNpadCommunicationMode(IN nn::applet::AppletResourceUserId _0, IN int64_t _1, IN gpid _2);
		uint32_t SetNpadHandheldActivationMode(IN nn::applet::AppletResourceUserId _0, IN int64_t _1, IN gpid _2);
		uint32_t SetNpadJoyAssignmentModeDual(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t SetNpadJoyAssignmentModeSingle(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN int64_t _2, IN gpid _3);
		uint32_t SetNpadJoyAssignmentModeSingleByDefault(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t SetNpadJoyHoldType(IN nn::applet::AppletResourceUserId _0, IN int64_t _1, IN gpid _2);
		uint32_t SetSixAxisSensorFusionParameters(IN nn::hid::SixAxisSensorHandle _0, IN float32_t _1, IN float32_t _2, IN nn::applet::AppletResourceUserId _3, IN gpid _4);
		uint32_t SetSupportedNpadIdType(IN nn::applet::AppletResourceUserId _0, IN gpid _1, IN uint32_t * _2, guint _2_size);
		uint32_t SetSupportedNpadStyleSet(IN nn::hid::NpadStyleTag _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t StartConsoleSixAxisSensor(IN nn::hid::ConsoleSixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t StartLrAssignmentMode(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t StartSixAxisSensor(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t StopConsoleSixAxisSensor(IN nn::hid::ConsoleSixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t StopLrAssignmentMode(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t StopSixAxisSensor(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t SwapNpadAssignment(IN uint32_t _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
	};
	class IHidSystemServer {
	public:
		IHidSystemServer();
		uint32_t AbortFirmwareUpdate();
		uint32_t AcquireCaptureButtonEventHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT KObject * _2);
		uint32_t AcquireConnectionTriggerTimeoutEvent(OUT KObject * _0);
		uint32_t AcquireDeviceRegisteredEventForControllerSupport(OUT KObject * _0);
		uint32_t AcquireHomeButtonEventHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT KObject * _2);
		uint32_t AcquireIrSensorEventHandle(IN uint32_t _0, OUT KObject * _1);
		uint32_t AcquireJoyDetachOnBluetoothOffEventHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT KObject * _2);
		uint32_t AcquireNfcActivateEventHandle(IN uint32_t _0, OUT KObject * _1);
		uint32_t AcquireNfcDeviceUpdateEventHandle(OUT KObject * _0);
		uint32_t AcquirePlayReportControllerUsageUpdateEvent(OUT KObject * _0);
		uint32_t AcquirePlayReportRegisteredDeviceUpdateEvent(OUT KObject * _0);
		uint32_t AcquireSleepButtonEventHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT KObject * _2);
		uint32_t AcquireUniquePadConnectionEventHandle(OUT KObject * _0);
		uint32_t ActivateCaptureButton(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t ActivateHomeButton(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t ActivateInputDetector(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t ActivateIrSensor(IN bool _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t ActivateNfc(IN bool _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t ActivateNpadSystem(IN uint32_t _0);
		uint32_t ActivateSleepButton(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t ActivateUniquePad(IN nn::applet::AppletResourceUserId _0, IN nn::hid::system::UniquePadId _1, IN gpid _2);
		uint32_t ApplyNpadSystemCommonPolicy(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t BeginPermitVibrationSession(IN nn::applet::AppletResourceUserId _0);
		uint32_t CancelAnalogStickManualCalibration(IN nn::hid::system::UniquePadId _0, IN int64_t _1);
		uint32_t CancelSixAxisSensorUserCalibration(IN nn::hid::system::UniqueSixAxisSensorHandle _0);
		uint32_t CheckFirmwareUpdateRequired(IN nn::hid::system::UniquePadId _0, OUT int64_t& _1);
		uint32_t DisableAssigningSingleOnSlSrPress(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t DisableHandheldHids();
		uint32_t DisconnectUniquePad(IN nn::hid::system::UniquePadId _0);
		uint32_t EnableAppletToGetInput(IN bool _0, IN nn::applet::AppletResourceUserId _1);
		uint32_t EnableAppletToGetSixAxisSensor(IN bool _0, IN nn::applet::AppletResourceUserId _1);
		uint32_t EnableAssigningSingleOnSlSrPress(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t EnableHandheldHids();
		uint32_t EnableUsbFullKeyController(IN bool _0);
		uint32_t EndPermitVibrationSession();
		uint32_t GetAllowedBluetoothLinksCount(OUT int64_t& _0);
		uint32_t GetAvailableFirmwareVersion(IN nn::hid::system::UniquePadId _0, OUT nn::hid::system::FirmwareVersion& _1);
		uint32_t GetFirmwareUpdateState(IN nn::hid::system::FirmwareUpdateDeviceHandle _0, OUT nn::hid::system::FirmwareUpdateState& _1);
		uint32_t GetFirmwareVersion(IN nn::hid::system::UniquePadId _0, OUT nn::hid::system::FirmwareVersion& _1);
		uint32_t GetIrSensorState(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT int64_t& _3);
		uint32_t GetLastActiveNpad(OUT uint32_t& _0);
		uint32_t GetNpadSystemExtStyle(IN uint32_t _0, OUT int64_t& _1, OUT int64_t& _2);
		uint32_t GetNpadsWithNfc(OUT int64_t& _0, OUT uint32_t * _1, guint _1_size);
		uint32_t GetPlayReportControllerUsages(OUT int64_t& _0, OUT nn::hid::system::PlayReportControllerUsage * _1, guint _1_size);
		uint32_t GetRegisteredDevices(OUT int64_t& _0, OUT nn::hid::system::RegisteredDevice * _1, guint _1_size);
		uint32_t GetUniquePadBluetoothAddress(IN nn::hid::system::UniquePadId _0, OUT nn::bluetooth::Address& _1);
		uint32_t GetUniquePadIds(OUT int64_t& _0, OUT nn::hid::system::UniquePadId * _1, guint _1_size);
		uint32_t GetUniquePadsFromNpad(IN uint32_t _0, OUT int64_t& _1, OUT nn::hid::system::UniquePadId * _2, guint _2_size);
		uint32_t GetVibrationMasterVolume(OUT float32_t& _0);
		uint32_t GetXcdHandleForNpadWithIrSensor(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT uint64_t& _3);
		uint32_t InitializeFirmwareUpdate();
		uint32_t IsFirmwareUpdateAvailable(IN nn::hid::system::UniquePadId _0, OUT bool& _1);
		uint32_t IsSixAxisSensorUserCalibrationSupported(IN nn::hid::system::UniqueSixAxisSensorHandle _0, OUT bool& _1);
		uint32_t IsUsbConnected(IN nn::hid::system::UniquePadId _0, OUT bool& _1);
		uint32_t IsUsbFullKeyControllerEnabled(OUT bool& _0);
		uint32_t ListSixAxisSensorHandles(IN nn::hid::system::UniquePadId _0, OUT int64_t& _1, OUT nn::hid::system::UniqueSixAxisSensorHandle * _2, guint _2_size);
		uint32_t NotifyInputDetector(IN nn::hid::system::InputSourceId _0);
		uint32_t RegisterAppletResourceUserId(IN bool _0, IN nn::applet::AppletResourceUserId _1);
		uint32_t ResetAnalogStickManualCalibration(IN nn::hid::system::UniquePadId _0, IN int64_t _1);
		uint32_t ResetSixAxisSensorCalibrationValues(IN nn::hid::system::UniqueSixAxisSensorHandle _0);
		uint32_t RetryCurrentAnalogStickManualCalibrationStage(IN nn::hid::system::UniquePadId _0, IN int64_t _1);
		uint32_t SendConnectionTrigger(IN nn::bluetooth::Address _0);
		uint32_t SendKeyboardLockKeyEvent(IN nn::hid::system::KeyboardLockKeyEvent _0);
		uint32_t SetAppletResourceUserId(IN nn::applet::AppletResourceUserId _0);
		uint32_t SetAruidValidForVibration(IN bool _0, IN nn::applet::AppletResourceUserId _1);
		uint32_t SetNpadPlayerLedBlinkingDevice(IN uint32_t _0, IN nn::hid::system::DeviceType _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t SetVibrationMasterVolume(IN float32_t _0);
		uint32_t StartAnalogStickManualCalibration(IN nn::hid::system::UniquePadId _0, IN int64_t _1);
		uint32_t StartFirmwareUpdate(IN nn::hid::system::UniquePadId _0, OUT nn::hid::system::FirmwareUpdateDeviceHandle& _1);
		uint32_t StartSixAxisSensorUserCalibration(IN nn::hid::system::UniqueSixAxisSensorHandle _0);
		uint32_t UnregisterAppletResourceUserId(IN nn::applet::AppletResourceUserId _0);
	};
	class IHidTemporaryServer {
	public:
		IHidTemporaryServer();
		uint32_t GetConsoleSixAxisSensorCalibrationValues(IN nn::hid::ConsoleSixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT nn::hid::tmp::ConsoleSixAxisSensorCalibrationValues& _3);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::hid::IActiveVibrationDeviceList::ActivateVibrationDevice(IN nn::hid::VibrationDeviceHandle _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IAppletResource::GetSharedMemoryHandle(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidDebugServer::ActivateFirmwareUpdate() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateCaptureButton() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateConsoleSixAxisSensor() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateDebugPad() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateFirmwareUpdate() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateGesture() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateHomeButton() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateInputDetector() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateJoyXpad(IN nn::hid::JoyXpadId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateKeyboard() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateMouse() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateSleepButton() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateTouchScreen() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DeactivateXpad(IN nn::hid::BasicXpadId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::DiscardFirmwareInfoCacheForRevert() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::GetAvailableFirmwareVersionForRevert(IN nn::hid::system::UniquePadId _0, OUT nn::hid::system::FirmwareVersion& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::GetDestinationFirmwareVersion(IN uint32_t _0, IN nn::hid::system::DeviceType _1, OUT nn::hid::system::FirmwareVersion& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::GetFirmwareUpdateStage(OUT int64_t& _0, OUT int64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::GetFirmwareVersion(IN uint32_t _0, IN nn::hid::system::DeviceType _1, OUT nn::hid::system::FirmwareVersion& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::GetShiftAccelerometerCalibrationValue(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT float32_t& _3, OUT float32_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::GetShiftGyroscopeCalibrationValue(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT float32_t& _3, OUT float32_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::SetCaptureButtonAutoPilotState(IN nn::hid::debug::CaptureButtonAutoPilotState _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::SetDebugPadAutoPilotState(IN nn::hid::debug::DebugPadAutoPilotState _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::SetHomeButtonAutoPilotState(IN nn::hid::debug::HomeButtonAutoPilotState _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::SetKeyboardAutoPilotState(IN nn::hid::debug::KeyboardAutoPilotState _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::SetMouseAutoPilotState(IN nn::hid::debug::MouseAutoPilotState _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::SetShiftAccelerometerCalibrationValue(IN nn::hid::SixAxisSensorHandle _0, IN float32_t _1, IN float32_t _2, IN nn::applet::AppletResourceUserId _3, IN gpid _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::SetShiftGyroscopeCalibrationValue(IN nn::hid::SixAxisSensorHandle _0, IN float32_t _1, IN float32_t _2, IN nn::applet::AppletResourceUserId _3, IN gpid _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::SetSleepButtonAutoPilotState(IN nn::hid::debug::SleepButtonAutoPilotState _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::SetTouchScreenAutoPilotState(IN nn::hid::TouchState * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::hid::IHidDebugServer::SetXpadAutoPilotState(IN nn::hid::BasicXpadId _0, IN nn::hid::debug::BasicXpadAutoPilotState _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::StartFirmwareUpdate(IN nn::hid::system::UniquePadId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::StartFirmwareUpdateForRevert(IN nn::hid::system::UniquePadId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::UnsetCaptureButtonAutoPilotState() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::UnsetDebugPadAutoPilotState() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::UnsetHomeButtonAutoPilotState() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::UnsetKeyboardAutoPilotState() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::UnsetMouseAutoPilotState() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::UnsetSleepButtonAutoPilotState() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::UnsetTouchScreenAutoPilotState() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::UnsetXpadAutoPilotState(IN nn::hid::BasicXpadId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidDebugServer::UpdateControllerColor(IN nn::util::Unorm8x4 _0, IN nn::util::Unorm8x4 _1, IN nn::hid::system::UniquePadId _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::AcquireNpadStyleSetUpdateEventHandle(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN uint64_t _2, IN gpid _3, OUT KObject * _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidServer::AcquireXpadIdEventHandle(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidServer::ActivateConsoleSixAxisSensor(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ActivateDebugPad(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ActivateGesture(IN int32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ActivateJoySixAxisSensor(IN nn::hid::JoyXpadId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ActivateJoyXpad(IN nn::hid::JoyXpadId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ActivateKeyboard(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ActivateMouse(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ActivateNpad(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ActivateSixAxisSensor(IN nn::hid::BasicXpadId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ActivateTouchScreen(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ActivateXpad(IN nn::hid::BasicXpadId _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::CreateActiveVibrationDeviceList(OUT nn::hid::IActiveVibrationDeviceList * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::hid::IActiveVibrationDeviceList(resp.move_handles[0]);
	return ret;
}
uint32_t nn::hid::IHidServer::CreateAppletResource(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT nn::hid::IAppletResource * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::hid::IAppletResource(resp.move_handles[0]);
	return ret;
}
uint32_t nn::hid::IHidServer::DeactivateJoySixAxisSensor(IN nn::hid::JoyXpadId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::DeactivateNpad(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::DeactivateSixAxisSensor(IN nn::hid::BasicXpadId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::DisconnectNpad(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::EnableSixAxisSensorFusion(IN bool _0, IN nn::hid::SixAxisSensorHandle _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::EnableUnintendedHomeButtonInputProtection(IN bool _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::EnableUsbFullKeyController(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetAccelerometerParameters(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT float32_t& _3, OUT float32_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetAccelerometerPlayMode(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetActualVibrationValue(IN nn::hid::VibrationDeviceHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT nn::hid::VibrationValue& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetGyroscopeZeroDriftMode(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetJoySixAxisSensorLifoHandle(IN nn::hid::JoyXpadId _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidServer::GetJoyXpadIds(OUT int64_t& _0, OUT nn::hid::JoyXpadId * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::hid::IHidServer::GetJoyXpadLifoHandle(IN nn::hid::JoyXpadId _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidServer::GetNpadCommunicationMode(OUT int64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetNpadHandheldActivationMode(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT int64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetNpadJoyHoldType(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT int64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetPlayerLedPattern(IN uint32_t _0, OUT uint64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetSixAxisSensorFusionParameters(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT float32_t& _3, OUT float32_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetSixAxisSensorLifoHandle(IN nn::hid::BasicXpadId _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidServer::GetSupportedNpadStyleSet(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT nn::hid::NpadStyleTag& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetVibrationDeviceInfo(IN nn::hid::VibrationDeviceHandle _0, OUT nn::hid::VibrationDeviceInfoForIpc& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::GetXpadIds(OUT int64_t& _0, OUT nn::hid::BasicXpadId * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::hid::IHidServer::IsSixAxisSensorAtRest(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT bool& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::IsSixAxisSensorFusionEnabled(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT bool& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::IsUnintendedHomeButtonInputProtectionEnabled(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT bool& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::IsUsbFullKeyControllerConnected(IN uint32_t _0, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::IsUsbFullKeyControllerEnabled(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::IsVibrationPermitted(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::MergeSingleJoyAsDualJoy(IN uint32_t _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::PermitVibration(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ReleaseXpadIdEventHandle(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ResetAccelerometerParameters(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ResetAccelerometerPlayMode(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ResetGyroscopeZeroDriftMode(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::ResetSixAxisSensorFusionParameters(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SendVibrationValue(IN nn::hid::VibrationDeviceHandle _0, IN nn::hid::VibrationValue _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SendVibrationValues(IN nn::applet::AppletResourceUserId _0, IN nn::hid::VibrationDeviceHandle * _1, guint _1_size, IN nn::hid::VibrationValue * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(9, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::hid::IHidServer::SetAccelerometerParameters(IN nn::hid::SixAxisSensorHandle _0, IN float32_t _1, IN float32_t _2, IN nn::applet::AppletResourceUserId _3, IN gpid _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SetAccelerometerPlayMode(IN nn::hid::SixAxisSensorHandle _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SetGyroscopeZeroDriftMode(IN nn::hid::SixAxisSensorHandle _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SetNpadCommunicationMode(IN nn::applet::AppletResourceUserId _0, IN int64_t _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SetNpadHandheldActivationMode(IN nn::applet::AppletResourceUserId _0, IN int64_t _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SetNpadJoyAssignmentModeDual(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SetNpadJoyAssignmentModeSingle(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN int64_t _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SetNpadJoyAssignmentModeSingleByDefault(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SetNpadJoyHoldType(IN nn::applet::AppletResourceUserId _0, IN int64_t _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SetSixAxisSensorFusionParameters(IN nn::hid::SixAxisSensorHandle _0, IN float32_t _1, IN float32_t _2, IN nn::applet::AppletResourceUserId _3, IN gpid _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SetSupportedNpadIdType(IN nn::applet::AppletResourceUserId _0, IN gpid _1, IN uint32_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::hid::IHidServer::SetSupportedNpadStyleSet(IN nn::hid::NpadStyleTag _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::StartConsoleSixAxisSensor(IN nn::hid::ConsoleSixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::StartLrAssignmentMode(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::StartSixAxisSensor(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::StopConsoleSixAxisSensor(IN nn::hid::ConsoleSixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::StopLrAssignmentMode(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::StopSixAxisSensor(IN nn::hid::SixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidServer::SwapNpadAssignment(IN uint32_t _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AbortFirmwareUpdate() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquireCaptureButtonEventHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquireConnectionTriggerTimeoutEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquireDeviceRegisteredEventForControllerSupport(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquireHomeButtonEventHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquireIrSensorEventHandle(IN uint32_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquireJoyDetachOnBluetoothOffEventHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquireNfcActivateEventHandle(IN uint32_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquireNfcDeviceUpdateEventHandle(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquirePlayReportControllerUsageUpdateEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquirePlayReportRegisteredDeviceUpdateEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquireSleepButtonEventHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::AcquireUniquePadConnectionEventHandle(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ActivateCaptureButton(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ActivateHomeButton(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ActivateInputDetector(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ActivateIrSensor(IN bool _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ActivateNfc(IN bool _0, IN uint32_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ActivateNpadSystem(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ActivateSleepButton(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ActivateUniquePad(IN nn::applet::AppletResourceUserId _0, IN nn::hid::system::UniquePadId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ApplyNpadSystemCommonPolicy(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::BeginPermitVibrationSession(IN nn::applet::AppletResourceUserId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::CancelAnalogStickManualCalibration(IN nn::hid::system::UniquePadId _0, IN int64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::CancelSixAxisSensorUserCalibration(IN nn::hid::system::UniqueSixAxisSensorHandle _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::CheckFirmwareUpdateRequired(IN nn::hid::system::UniquePadId _0, OUT int64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::DisableAssigningSingleOnSlSrPress(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::DisableHandheldHids() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::DisconnectUniquePad(IN nn::hid::system::UniquePadId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::EnableAppletToGetInput(IN bool _0, IN nn::applet::AppletResourceUserId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::EnableAppletToGetSixAxisSensor(IN bool _0, IN nn::applet::AppletResourceUserId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::EnableAssigningSingleOnSlSrPress(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::EnableHandheldHids() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::EnableUsbFullKeyController(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::EndPermitVibrationSession() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetAllowedBluetoothLinksCount(OUT int64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetAvailableFirmwareVersion(IN nn::hid::system::UniquePadId _0, OUT nn::hid::system::FirmwareVersion& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetFirmwareUpdateState(IN nn::hid::system::FirmwareUpdateDeviceHandle _0, OUT nn::hid::system::FirmwareUpdateState& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetFirmwareVersion(IN nn::hid::system::UniquePadId _0, OUT nn::hid::system::FirmwareVersion& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetIrSensorState(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT int64_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetLastActiveNpad(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetNpadSystemExtStyle(IN uint32_t _0, OUT int64_t& _1, OUT int64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetNpadsWithNfc(OUT int64_t& _0, OUT uint32_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetPlayReportControllerUsages(OUT int64_t& _0, OUT nn::hid::system::PlayReportControllerUsage * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetRegisteredDevices(OUT int64_t& _0, OUT nn::hid::system::RegisteredDevice * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetUniquePadBluetoothAddress(IN nn::hid::system::UniquePadId _0, OUT nn::bluetooth::Address& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::bluetooth::Address>(0xc);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetUniquePadIds(OUT int64_t& _0, OUT nn::hid::system::UniquePadId * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetUniquePadsFromNpad(IN uint32_t _0, OUT int64_t& _1, OUT nn::hid::system::UniquePadId * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetVibrationMasterVolume(OUT float32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::GetXcdHandleForNpadWithIrSensor(IN uint32_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT uint64_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::InitializeFirmwareUpdate() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::IsFirmwareUpdateAvailable(IN nn::hid::system::UniquePadId _0, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::IsSixAxisSensorUserCalibrationSupported(IN nn::hid::system::UniqueSixAxisSensorHandle _0, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::IsUsbConnected(IN nn::hid::system::UniquePadId _0, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::IsUsbFullKeyControllerEnabled(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ListSixAxisSensorHandles(IN nn::hid::system::UniquePadId _0, OUT int64_t& _1, OUT nn::hid::system::UniqueSixAxisSensorHandle * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::hid::IHidSystemServer::NotifyInputDetector(IN nn::hid::system::InputSourceId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::RegisterAppletResourceUserId(IN bool _0, IN nn::applet::AppletResourceUserId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ResetAnalogStickManualCalibration(IN nn::hid::system::UniquePadId _0, IN int64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::ResetSixAxisSensorCalibrationValues(IN nn::hid::system::UniqueSixAxisSensorHandle _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::RetryCurrentAnalogStickManualCalibrationStage(IN nn::hid::system::UniquePadId _0, IN int64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::SendConnectionTrigger(IN nn::bluetooth::Address _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::SendKeyboardLockKeyEvent(IN nn::hid::system::KeyboardLockKeyEvent _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::SetAppletResourceUserId(IN nn::applet::AppletResourceUserId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::SetAruidValidForVibration(IN bool _0, IN nn::applet::AppletResourceUserId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::SetNpadPlayerLedBlinkingDevice(IN uint32_t _0, IN nn::hid::system::DeviceType _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::SetVibrationMasterVolume(IN float32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::StartAnalogStickManualCalibration(IN nn::hid::system::UniquePadId _0, IN int64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::StartFirmwareUpdate(IN nn::hid::system::UniquePadId _0, OUT nn::hid::system::FirmwareUpdateDeviceHandle& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::StartSixAxisSensorUserCalibration(IN nn::hid::system::UniqueSixAxisSensorHandle _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidSystemServer::UnregisterAppletResourceUserId(IN nn::applet::AppletResourceUserId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::hid::IHidTemporaryServer::GetConsoleSixAxisSensorCalibrationValues(IN nn::hid::ConsoleSixAxisSensorHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT nn::hid::tmp::ConsoleSixAxisSensorCalibrationValues& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::hid::tmp::ConsoleSixAxisSensorCalibrationValues>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::htc::tenv {
	class IService {
	public:
		IService();
		uint32_t Unknown0(IN uint8_t * _0, OUT uint64_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown1(IN uint8_t * _0, OUT uint64_t& _1);
		uint32_t Unknown2(IN uint64_t _0);
	};
	class IServiceManager {
	public:
		IServiceManager();
		uint32_t Unknown0(IN uint64_t _0, IN gpid _1, OUT IUnknown * _2);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::htc::tenv::IService::Unknown0(IN uint8_t * _0, OUT uint64_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::htc::tenv::IService::Unknown1(IN uint8_t * _0, OUT uint64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::htc::tenv::IService::Unknown2(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::htc::tenv::IServiceManager::Unknown0(IN uint64_t _0, IN gpid _1, OUT IUnknown * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::i2c {
	class IManager {
	public:
		IManager();
		uint32_t Unknown0(IN uint16_t _0, IN uint32_t _1, IN uint32_t _2, IN uint32_t _3, OUT IUnknown * _4);
		uint32_t Unknown1(IN uint32_t _0, OUT IUnknown * _1);
		uint32_t Unknown2(IN uint32_t _0, OUT uint8_t& _1);
		uint32_t Unknown3(IN uint16_t _0, IN uint32_t _1, IN uint32_t _2, IN uint32_t _3, OUT uint8_t& _4);
	};
	class ISession {
	public:
		ISession();
		uint32_t Unknown0(IN uint32_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown1(IN uint32_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown10(IN uint32_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown11(IN uint32_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown12(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown2(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::i2c::IManager::Unknown0(IN uint16_t _0, IN uint32_t _1, IN uint32_t _2, IN uint32_t _3, OUT IUnknown * _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_4 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::i2c::IManager::Unknown1(IN uint32_t _0, OUT IUnknown * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::i2c::IManager::Unknown2(IN uint32_t _0, OUT uint8_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::i2c::IManager::Unknown3(IN uint16_t _0, IN uint32_t _1, IN uint32_t _2, IN uint32_t _3, OUT uint8_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::i2c::ISession::Unknown0(IN uint32_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::i2c::ISession::Unknown1(IN uint32_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::i2c::ISession::Unknown10(IN uint32_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::i2c::ISession::Unknown11(IN uint32_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::i2c::ISession::Unknown12(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x22, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::i2c::ISession::Unknown2(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::idle::detail {
	class IPolicyManagerSystem {
	public:
		IPolicyManagerSystem();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::idle::detail::IPolicyManagerSystem::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::idle::detail::IPolicyManagerSystem::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::idle::detail::IPolicyManagerSystem::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::idle::detail::IPolicyManagerSystem::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::idle::detail::IPolicyManagerSystem::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::idle::detail::IPolicyManagerSystem::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::irsensor {
	class IIrSensorServer {
	public:
		IIrSensorServer();
		uint32_t ActivateIrsensor(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t CheckFirmwareVersion(IN nn::irsensor::IrCameraHandle _0, IN nn::irsensor::PackedMcuVersion _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t DeactivateIrsensor(IN nn::applet::AppletResourceUserId _0, IN gpid _1);
		uint32_t GetImageTransferProcessorState(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT nn::irsensor::ImageTransferProcessorState& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t GetIrsensorSharedMemoryHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT KObject * _2);
		uint32_t GetNpadIrCameraHandle(IN uint32_t _0, OUT nn::irsensor::IrCameraHandle& _1);
		uint32_t RunClusteringProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN nn::irsensor::PackedClusteringProcessorConfig _2, IN gpid _3);
		uint32_t RunDpdProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::irsensor::PackedDpdProcessorConfig _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t RunImageTransferProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN nn::irsensor::PackedImageTransferProcessorConfig _2, IN uint64_t _3, IN gpid _4, IN KObject * _5);
		uint32_t RunMomentProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN nn::irsensor::PackedMomentProcessorConfig _2, IN gpid _3);
		uint32_t RunTeraPluginProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::irsensor::PackedTeraPluginProcessorConfig _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3);
		uint32_t StopImageProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
		uint32_t SuspendImageProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2);
	};
	class IIrSensorSystemServer {
	public:
		IIrSensorSystemServer();
		uint32_t EnableAppletToGetInput(IN bool _0, IN nn::applet::AppletResourceUserId _1);
		uint32_t RegisterAppletResourceUserId(IN bool _0, IN nn::applet::AppletResourceUserId _1);
		uint32_t SetAppletResourceUserId(IN nn::applet::AppletResourceUserId _0);
		uint32_t UnregisterAppletResourceUserId(IN nn::applet::AppletResourceUserId _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::irsensor::IIrSensorServer::ActivateIrsensor(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::CheckFirmwareVersion(IN nn::irsensor::IrCameraHandle _0, IN nn::irsensor::PackedMcuVersion _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::DeactivateIrsensor(IN nn::applet::AppletResourceUserId _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::GetImageTransferProcessorState(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT nn::irsensor::ImageTransferProcessorState& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::GetIrsensorSharedMemoryHandle(IN nn::applet::AppletResourceUserId _0, IN gpid _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::GetNpadIrCameraHandle(IN uint32_t _0, OUT nn::irsensor::IrCameraHandle& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::RunClusteringProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN nn::irsensor::PackedClusteringProcessorConfig _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::RunDpdProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::irsensor::PackedDpdProcessorConfig _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::RunImageTransferProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN nn::irsensor::PackedImageTransferProcessorConfig _2, IN uint64_t _3, IN gpid _4, IN KObject * _5) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::RunMomentProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN nn::irsensor::PackedMomentProcessorConfig _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::RunTeraPluginProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::irsensor::PackedTeraPluginProcessorConfig _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::StopImageProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorServer::SuspendImageProcessor(IN nn::irsensor::IrCameraHandle _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorSystemServer::EnableAppletToGetInput(IN bool _0, IN nn::applet::AppletResourceUserId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorSystemServer::RegisterAppletResourceUserId(IN bool _0, IN nn::applet::AppletResourceUserId _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorSystemServer::SetAppletResourceUserId(IN nn::applet::AppletResourceUserId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::irsensor::IIrSensorSystemServer::UnregisterAppletResourceUserId(IN nn::applet::AppletResourceUserId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::lbl::detail {
	class ILblController {
	public:
		ILblController();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown14();
		uint32_t Unknown15();
		uint32_t Unknown16();
		uint32_t Unknown17();
		uint32_t Unknown18();
		uint32_t Unknown19();
		uint32_t Unknown2();
		uint32_t Unknown20();
		uint32_t Unknown21();
		uint32_t Unknown22();
		uint32_t Unknown23();
		uint32_t Unknown24();
		uint32_t Unknown25();
		uint32_t Unknown26();
		uint32_t Unknown27();
		uint32_t Unknown28();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::lbl::detail::ILblController::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown14() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown15() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown16() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown17() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown18() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown19() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown20() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown21() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown22() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown23() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown24() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown25() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown26() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown27() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown28() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::lbl::detail::ILblController::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::ldn::detail {
	class IMonitorService {
	public:
		IMonitorService();
		uint32_t Unknown0(OUT uint32_t& _0);
		uint32_t Unknown1(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown100();
		uint32_t Unknown101();
		uint32_t Unknown2(OUT uint32_t& _0, OUT uint32_t& _1);
		uint32_t Unknown3(OUT uint16_t& _0);
		uint32_t Unknown4(OUT uint8_t * _0);
		uint32_t Unknown5(OUT uint8_t * _0);
	};
	class IMonitorServiceCreator {
	public:
		IMonitorServiceCreator();
		uint32_t Unknown0(OUT IUnknown * _0);
	};
	class ISystemLocalCommunicationService {
	public:
		ISystemLocalCommunicationService();
		uint32_t Unknown0(OUT uint32_t& _0);
		uint32_t Unknown1(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown100(OUT KObject * _0);
		uint32_t Unknown101(OUT uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown102(IN uint16_t _0, IN uint8_t * _1, OUT uint16_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t Unknown103(IN uint16_t _0, IN uint8_t * _1, OUT uint16_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t Unknown2(OUT uint32_t& _0, OUT uint32_t& _1);
		uint32_t Unknown200();
		uint32_t Unknown201();
		uint32_t Unknown202(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2);
		uint32_t Unknown203(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2, IN uint8_t * _3, IN uint8_t * _4, guint _4_size);
		uint32_t Unknown204();
		uint32_t Unknown205(IN uint32_t _0);
		uint32_t Unknown206(IN uint8_t * _0, guint _0_size);
		uint32_t Unknown207(IN uint8_t _0);
		uint32_t Unknown208(IN uint8_t * _0);
		uint32_t Unknown209();
		uint32_t Unknown3(OUT uint16_t& _0);
		uint32_t Unknown300();
		uint32_t Unknown301();
		uint32_t Unknown302(IN uint8_t * _0, IN uint8_t * _1, IN uint32_t _2, IN uint32_t _3, IN uint8_t * _4, guint _4_size);
		uint32_t Unknown303(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2, IN uint32_t _3, IN uint32_t _4, IN uint8_t * _5);
		uint32_t Unknown304();
		uint32_t Unknown4(OUT uint8_t * _0);
		uint32_t Unknown400(IN uint64_t _0, IN gpid _1);
		uint32_t Unknown401();
		uint32_t Unknown5(OUT uint8_t * _0);
	};
	class ISystemServiceCreator {
	public:
		ISystemServiceCreator();
		uint32_t Unknown0(OUT IUnknown * _0);
	};
	class IUserLocalCommunicationService {
	public:
		IUserLocalCommunicationService();
		uint32_t Unknown0(OUT uint32_t& _0);
		uint32_t Unknown1(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown100(OUT KObject * _0);
		uint32_t Unknown101(OUT uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown102(IN uint16_t _0, IN uint8_t * _1, OUT uint16_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t Unknown103(IN uint16_t _0, IN uint8_t * _1, OUT uint16_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t Unknown2(OUT uint32_t& _0, OUT uint32_t& _1);
		uint32_t Unknown200();
		uint32_t Unknown201();
		uint32_t Unknown202(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2);
		uint32_t Unknown203(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2, IN uint8_t * _3, IN uint8_t * _4, guint _4_size);
		uint32_t Unknown204();
		uint32_t Unknown205(IN uint32_t _0);
		uint32_t Unknown206(IN uint8_t * _0, guint _0_size);
		uint32_t Unknown207(IN uint8_t _0);
		uint32_t Unknown208(IN uint8_t * _0);
		uint32_t Unknown209();
		uint32_t Unknown3(OUT uint16_t& _0);
		uint32_t Unknown300();
		uint32_t Unknown301();
		uint32_t Unknown302(IN uint8_t * _0, IN uint8_t * _1, IN uint32_t _2, IN uint32_t _3, IN uint8_t * _4, guint _4_size);
		uint32_t Unknown303(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2, IN uint32_t _3, IN uint32_t _4, IN uint8_t * _5);
		uint32_t Unknown304();
		uint32_t Unknown4(OUT uint8_t * _0);
		uint32_t Unknown400(IN uint64_t _0, IN gpid _1);
		uint32_t Unknown401();
		uint32_t Unknown5(OUT uint8_t * _0);
	};
	class IUserServiceCreator {
	public:
		IUserServiceCreator();
		uint32_t Unknown0(OUT IUnknown * _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::ldn::detail::IMonitorService::Unknown0(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IMonitorService::Unknown1(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::IMonitorService::Unknown100() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IMonitorService::Unknown101() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IMonitorService::Unknown2(OUT uint32_t& _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IMonitorService::Unknown3(OUT uint16_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IMonitorService::Unknown4(OUT uint8_t * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IMonitorService::Unknown5(OUT uint8_t * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IMonitorServiceCreator::Unknown0(OUT IUnknown * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown0(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown1(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown100(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown101(OUT uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0xa, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown102(IN uint16_t _0, IN uint8_t * _1, OUT uint16_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown103(IN uint16_t _0, IN uint8_t * _1, OUT uint16_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown2(OUT uint32_t& _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown200() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown201() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown202(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown203(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2, IN uint8_t * _3, IN uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown204() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown205(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown206(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown207(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown208(IN uint8_t * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown209() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown3(OUT uint16_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown300() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown301() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown302(IN uint8_t * _0, IN uint8_t * _1, IN uint32_t _2, IN uint32_t _3, IN uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown303(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2, IN uint32_t _3, IN uint32_t _4, IN uint8_t * _5) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown304() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown4(OUT uint8_t * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown400(IN uint64_t _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown401() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemLocalCommunicationService::Unknown5(OUT uint8_t * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::ISystemServiceCreator::Unknown0(OUT IUnknown * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown0(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown1(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown100(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown101(OUT uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0xa, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown102(IN uint16_t _0, IN uint8_t * _1, OUT uint16_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown103(IN uint16_t _0, IN uint8_t * _1, OUT uint16_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown2(OUT uint32_t& _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown200() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown201() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown202(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown203(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2, IN uint8_t * _3, IN uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown204() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown205(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown206(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown207(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown208(IN uint8_t * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown209() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown3(OUT uint16_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown300() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown301() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown302(IN uint8_t * _0, IN uint8_t * _1, IN uint32_t _2, IN uint32_t _3, IN uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown303(IN uint8_t * _0, IN uint8_t * _1, IN uint8_t * _2, IN uint32_t _3, IN uint32_t _4, IN uint8_t * _5) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown304() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown4(OUT uint8_t * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown400(IN uint64_t _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown401() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserLocalCommunicationService::Unknown5(OUT uint8_t * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ldn::detail::IUserServiceCreator::Unknown0(OUT IUnknown * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::lm {
	class ILogService {
	public:
		ILogService();
		uint32_t Initialize(IN uint64_t _0, IN gpid _1, OUT nn::lm::ILogger * Log);
	};
	class ILogger {
	public:
		ILogger();
		uint32_t Unknown0(IN uint8_t * _0, guint _0_size);
		uint32_t Unknown1(IN uint32_t _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::lm::ILogService::Initialize(IN uint64_t _0, IN gpid _1, OUT nn::lm::ILogger * Log) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	Log OMG = new nn::lm::ILogger(resp.move_handles[0]);
	return ret;
}
uint32_t nn::lm::ILogger::Unknown0(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::lm::ILogger::Unknown1(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::mii::detail {
	class IDatabaseService {
	public:
		IDatabaseService();
		uint32_t AddOrReplace(IN nn::mii::StoreData _0);
		uint32_t BuildDefault(IN int32_t _0, OUT nn::mii::CharInfo& _1);
		uint32_t BuildRandom(IN int32_t _0, IN int32_t _1, IN int32_t _2, OUT nn::mii::CharInfo& _3);
		uint32_t Delete(IN nn::mii::CreateId _0);
		uint32_t DeleteFile();
		uint32_t DestroyFile();
		uint32_t Export(OUT uint8_t * _0, guint _0_size);
		uint32_t FindIndex(IN nn::mii::CreateId _0, IN bool _1, OUT int32_t& _2);
		uint32_t Format();
		uint32_t Get(IN int32_t _0, OUT int32_t& _1, OUT nn::mii::CharInfoElement * _2, guint _2_size);
		uint32_t Get1(IN int32_t _0, OUT int32_t& _1, OUT nn::mii::CharInfo * _2, guint _2_size);
		uint32_t Get2(IN int32_t _0, OUT int32_t& _1, OUT nn::mii::StoreDataElement * _2, guint _2_size);
		uint32_t Get3(IN int32_t _0, OUT int32_t& _1, OUT nn::mii::StoreData * _2, guint _2_size);
		uint32_t GetCount(IN int32_t _0, OUT int32_t& _1);
		uint32_t GetIndex(IN nn::mii::CharInfo _0, OUT int32_t& _1);
		uint32_t Import(IN uint8_t * _0, guint _0_size);
		uint32_t IsBrokenDatabaseWithClearFlag(OUT bool& _0);
		uint32_t IsFullDatabase(OUT bool& _0);
		uint32_t IsUpdated(IN int32_t _0, OUT bool& _1);
		uint32_t Move(IN nn::mii::CreateId _0, IN int32_t _1);
		uint32_t UpdateLatest(IN nn::mii::CharInfo _0, IN int32_t _1, OUT nn::mii::CharInfo& _2);
		uint32_t UpdateLatest1(IN nn::mii::StoreData _0, IN int32_t _1, OUT nn::mii::StoreData& _2);
	};
	class IStaticService {
	public:
		IStaticService();
		uint32_t GetDatabaseService(IN int32_t _0, OUT nn::mii::detail::IDatabaseService * _1);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::mii::detail::IDatabaseService::AddOrReplace(IN nn::mii::StoreData _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::BuildDefault(IN int32_t _0, OUT nn::mii::CharInfo& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::mii::CharInfo>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::BuildRandom(IN int32_t _0, IN int32_t _1, IN int32_t _2, OUT nn::mii::CharInfo& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::mii::CharInfo>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::Delete(IN nn::mii::CreateId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::DeleteFile() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::DestroyFile() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::Export(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::FindIndex(IN nn::mii::CreateId _0, IN bool _1, OUT int32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::Format() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::Get(IN int32_t _0, OUT int32_t& _1, OUT nn::mii::CharInfoElement * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::Get1(IN int32_t _0, OUT int32_t& _1, OUT nn::mii::CharInfo * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::Get2(IN int32_t _0, OUT int32_t& _1, OUT nn::mii::StoreDataElement * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::Get3(IN int32_t _0, OUT int32_t& _1, OUT nn::mii::StoreData * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::GetCount(IN int32_t _0, OUT int32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::GetIndex(IN nn::mii::CharInfo _0, OUT int32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::Import(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::IsBrokenDatabaseWithClearFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::IsFullDatabase(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::IsUpdated(IN int32_t _0, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::Move(IN nn::mii::CreateId _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::UpdateLatest(IN nn::mii::CharInfo _0, IN int32_t _1, OUT nn::mii::CharInfo& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::mii::CharInfo>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IDatabaseService::UpdateLatest1(IN nn::mii::StoreData _0, IN int32_t _1, OUT nn::mii::StoreData& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::mii::StoreData>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mii::detail::IStaticService::GetDatabaseService(IN int32_t _0, OUT nn::mii::detail::IDatabaseService * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::mii::detail::IDatabaseService(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::mmnv {
	class IRequest {
	public:
		IRequest();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::mmnv::IRequest::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mmnv::IRequest::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mmnv::IRequest::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mmnv::IRequest::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mmnv::IRequest::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mmnv::IRequest::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mmnv::IRequest::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::mmnv::IRequest::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::ncm::detail {
	class INcmInterface {
	public:
		INcmInterface();
		uint32_t Unknown11(OUT uint64_t& _0);
		uint32_t Unknown2(OUT uint64_t& _0);
		uint32_t Unknown3(OUT uint64_t& _0);
		uint32_t Unknown4(OUT nn::ncm::detail::INcmInterface4Unknown * _0);
		uint32_t Unknown5(OUT nn::ncm::detail::INcmInterface5Unknown * _0);
		uint32_t Unknown9(OUT uint64_t& _0);
	};
	class INcmInterface4Unknown {
	public:
		INcmInterface4Unknown();
		uint32_t Unknown10();
		uint32_t Unknown13(OUT uint64_t& _0);
	};
	class INcmInterface5Unknown {
	public:
		INcmInterface5Unknown();
		uint32_t Unknown15();
		uint32_t Unknown5(OUT uint64_t& _0);
		uint32_t Unknown7(OUT uint64_t& _0);
		uint32_t Unknown8();
	};
	class LocationResolverInterface {
	public:
		LocationResolverInterface();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::ncm::detail::INcmInterface::Unknown11(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ncm::detail::INcmInterface::Unknown2(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ncm::detail::INcmInterface::Unknown3(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ncm::detail::INcmInterface::Unknown4(OUT nn::ncm::detail::INcmInterface4Unknown * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::ncm::detail::INcmInterface4Unknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::ncm::detail::INcmInterface::Unknown5(OUT nn::ncm::detail::INcmInterface5Unknown * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::ncm::detail::INcmInterface5Unknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::ncm::detail::INcmInterface::Unknown9(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ncm::detail::INcmInterface4Unknown::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ncm::detail::INcmInterface4Unknown::Unknown13(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ncm::detail::INcmInterface5Unknown::Unknown15() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ncm::detail::INcmInterface5Unknown::Unknown5(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ncm::detail::INcmInterface5Unknown::Unknown7(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ncm::detail::INcmInterface5Unknown::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::news::detail::ipc {
	class INewlyArrivedEventHolder {
	public:
		INewlyArrivedEventHolder();
		uint32_t Unknown0();
	};
	class INewsDataService {
	public:
		INewsDataService();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
	};
	class INewsDatabaseService {
	public:
		INewsDatabaseService();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
	};
	class INewsService {
	public:
		INewsService();
		uint32_t Unknown10100();
		uint32_t Unknown20100();
		uint32_t Unknown30100();
		uint32_t Unknown30101();
		uint32_t Unknown30200();
		uint32_t Unknown30400();
		uint32_t Unknown40100();
		uint32_t Unknown40101();
		uint32_t Unknown90100();
	};
	class IOverwriteEventHolder {
	public:
		IOverwriteEventHolder();
		uint32_t Unknown0();
	};
	class IServiceCreator {
	public:
		IServiceCreator();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::news::detail::ipc::INewlyArrivedEventHolder::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsDataService::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsDataService::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsDataService::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsDataService::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsDatabaseService::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsDatabaseService::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsDatabaseService::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsDatabaseService::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsDatabaseService::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsDatabaseService::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsService::Unknown10100() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsService::Unknown20100() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsService::Unknown30100() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsService::Unknown30101() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsService::Unknown30200() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsService::Unknown30400() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsService::Unknown40100() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsService::Unknown40101() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::INewsService::Unknown90100() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::IOverwriteEventHolder::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::IServiceCreator::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::IServiceCreator::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::IServiceCreator::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::IServiceCreator::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::news::detail::ipc::IServiceCreator::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::nfc::am::detail {
	class IAm {
	public:
		IAm();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
	};
	class IAmManager {
	public:
		IAmManager();
		uint32_t Unknown0();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::nfc::am::detail::IAm::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::am::detail::IAm::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::am::detail::IAm::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::am::detail::IAmManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::nfc::detail {
	class ISystem {
	public:
		ISystem();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size);
		uint32_t Unknown1();
		uint32_t Unknown100(IN uint8_t _0);
		uint32_t Unknown2(OUT uint32_t& _0);
		uint32_t Unknown3(OUT uint8_t& _0);
	};
	class ISystemManager {
	public:
		ISystemManager();
		uint32_t Unknown0(OUT IUnknown * _0);
	};
	class IUser {
	public:
		IUser();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size);
		uint32_t Unknown1();
		uint32_t Unknown2(OUT uint32_t& _0);
		uint32_t Unknown3(OUT uint8_t& _0);
	};
	class IUserManager {
	public:
		IUserManager();
		uint32_t Unknown0(OUT IUnknown * _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::nfc::detail::ISystem::Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfc::detail::ISystem::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::detail::ISystem::Unknown100(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::detail::ISystem::Unknown2(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::detail::ISystem::Unknown3(OUT uint8_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::detail::ISystemManager::Unknown0(OUT IUnknown * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::nfc::detail::IUser::Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfc::detail::IUser::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::detail::IUser::Unknown2(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::detail::IUser::Unknown3(OUT uint8_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::detail::IUserManager::Unknown0(OUT IUnknown * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::nfc::mifare::detail {
	class IUser {
	public:
		IUser();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size);
		uint32_t Unknown1();
		uint32_t Unknown10(OUT uint32_t& _0);
		uint32_t Unknown11(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown12(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown13(OUT KObject * _0);
		uint32_t Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown3(IN uint64_t _0);
		uint32_t Unknown4(IN uint64_t _0);
		uint32_t Unknown5(IN uint64_t _0, IN uint8_t * _1, guint _1_size, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown6(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown7(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown8(IN uint64_t _0, OUT KObject * _1);
		uint32_t Unknown9(IN uint64_t _0, OUT KObject * _1);
	};
	class IUserManager {
	public:
		IUserManager();
		uint32_t Unknown0(OUT IUnknown * _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::nfc::mifare::detail::IUser::Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown10(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown11(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown12(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown13(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown3(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown4(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown5(IN uint64_t _0, IN uint8_t * _1, guint _1_size, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown6(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown7(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown8(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUser::Unknown9(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfc::mifare::detail::IUserManager::Unknown0(OUT IUnknown * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::nfp::detail {
	class IDebug {
	public:
		IDebug();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size);
		uint32_t Unknown1();
		uint32_t Unknown10(IN uint64_t _0);
		uint32_t Unknown100(IN uint64_t _0);
		uint32_t Unknown101(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown102(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown103(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown104(IN uint64_t _0);
		uint32_t Unknown105(IN uint64_t _0);
		uint32_t Unknown106(IN uint64_t _0, OUT uint8_t& _1);
		uint32_t Unknown11(IN uint64_t _0);
		uint32_t Unknown12(IN uint64_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size);
		uint32_t Unknown13(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown14(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown15(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown16(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown17(IN uint64_t _0, OUT KObject * _1);
		uint32_t Unknown18(IN uint64_t _0, OUT KObject * _1);
		uint32_t Unknown19(OUT uint32_t& _0);
		uint32_t Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown20(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown200(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown201(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown202(IN uint64_t _0);
		uint32_t Unknown203(IN uint64_t _0, IN uint32_t _1);
		uint32_t Unknown204(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown205(IN uint8_t * _0, guint _0_size);
		uint32_t Unknown206(IN uint64_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size);
		uint32_t Unknown21(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown22(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown23(OUT KObject * _0);
		uint32_t Unknown24(IN uint64_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size);
		uint32_t Unknown3(IN uint64_t _0);
		uint32_t Unknown300(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size);
		uint32_t Unknown301();
		uint32_t Unknown302(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown303(IN uint64_t _0, IN uint32_t _1);
		uint32_t Unknown304(IN uint64_t _0);
		uint32_t Unknown305(IN uint64_t _0, IN uint64_t _1, IN uint8_t * _2, guint _2_size, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t Unknown306(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown307(IN uint64_t _0, OUT KObject * _1);
		uint32_t Unknown308(IN uint64_t _0, OUT KObject * _1);
		uint32_t Unknown309(OUT uint32_t& _0);
		uint32_t Unknown310(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown311(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown312(IN uint64_t _0);
		uint32_t Unknown313(IN uint64_t _0);
		uint32_t Unknown314(OUT KObject * _0);
		uint32_t Unknown4(IN uint64_t _0);
		uint32_t Unknown5(IN uint64_t _0, IN uint32_t _1, IN uint32_t _2);
		uint32_t Unknown6(IN uint64_t _0);
		uint32_t Unknown7(IN uint64_t _0, IN uint32_t _1);
		uint32_t Unknown8(IN uint64_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown9(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
	};
	class IDebugManager {
	public:
		IDebugManager();
		uint32_t Unknown0(OUT IUnknown * _0);
	};
	class ISystem {
	public:
		ISystem();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size);
		uint32_t Unknown1();
		uint32_t Unknown10(IN uint64_t _0);
		uint32_t Unknown100(IN uint64_t _0);
		uint32_t Unknown101(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown102(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown103(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown104(IN uint64_t _0);
		uint32_t Unknown105(IN uint64_t _0);
		uint32_t Unknown106(IN uint64_t _0, OUT uint8_t& _1);
		uint32_t Unknown11(IN uint64_t _0);
		uint32_t Unknown13(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown14(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown15(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown16(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown17(IN uint64_t _0, OUT KObject * _1);
		uint32_t Unknown18(IN uint64_t _0, OUT KObject * _1);
		uint32_t Unknown19(OUT uint32_t& _0);
		uint32_t Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown20(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown21(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown23(OUT KObject * _0);
		uint32_t Unknown3(IN uint64_t _0);
		uint32_t Unknown4(IN uint64_t _0);
		uint32_t Unknown5(IN uint64_t _0, IN uint32_t _1, IN uint32_t _2);
		uint32_t Unknown6(IN uint64_t _0);
	};
	class ISystemManager {
	public:
		ISystemManager();
		uint32_t Unknown0(OUT IUnknown * _0);
	};
	class IUser {
	public:
		IUser();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size);
		uint32_t Unknown1();
		uint32_t Unknown10(IN uint64_t _0);
		uint32_t Unknown11(IN uint64_t _0);
		uint32_t Unknown12(IN uint64_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size);
		uint32_t Unknown13(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown14(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown15(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown16(IN uint64_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown17(IN uint64_t _0, OUT KObject * _1);
		uint32_t Unknown18(IN uint64_t _0, OUT KObject * _1);
		uint32_t Unknown19(OUT uint32_t& _0);
		uint32_t Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown20(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown21(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown22(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t Unknown23(OUT KObject * _0);
		uint32_t Unknown24(IN uint64_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size);
		uint32_t Unknown3(IN uint64_t _0);
		uint32_t Unknown4(IN uint64_t _0);
		uint32_t Unknown5(IN uint64_t _0, IN uint32_t _1, IN uint32_t _2);
		uint32_t Unknown6(IN uint64_t _0);
		uint32_t Unknown7(IN uint64_t _0, IN uint32_t _1);
		uint32_t Unknown8(IN uint64_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown9(IN uint64_t _0, IN uint8_t * _1, guint _1_size);
	};
	class IUserManager {
	public:
		IUserManager();
		uint32_t Unknown0(OUT IUnknown * _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::nfp::detail::IDebug::Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown10(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown100(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown101(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown102(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown103(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown104(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown105(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown106(IN uint64_t _0, OUT uint8_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown11(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown12(IN uint64_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown13(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown14(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown15(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown16(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown17(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown18(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown19(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown20(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown200(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown201(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown202(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown203(IN uint64_t _0, IN uint32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown204(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown205(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown206(IN uint64_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown21(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown22(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown23(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown24(IN uint64_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown3(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown300(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown301() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown302(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown303(IN uint64_t _0, IN uint32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown304(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown305(IN uint64_t _0, IN uint64_t _1, IN uint8_t * _2, guint _2_size, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown306(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown307(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown308(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown309(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown310(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown311(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown312(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown313(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown314(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown4(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown5(IN uint64_t _0, IN uint32_t _1, IN uint32_t _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown6(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown7(IN uint64_t _0, IN uint32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown8(IN uint64_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebug::Unknown9(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IDebugManager::Unknown0(OUT IUnknown * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown10(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown100(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown101(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown102(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown103(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown104(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown105(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown106(IN uint64_t _0, OUT uint8_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown11(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown13(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown14(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown15(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown16(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown17(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown18(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown19(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown20(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown21(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown23(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown3(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown4(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown5(IN uint64_t _0, IN uint32_t _1, IN uint32_t _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystem::Unknown6(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::ISystemManager::Unknown0(OUT IUnknown * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown0(IN uint64_t _0, IN uint64_t _1, IN gpid _2, IN uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown10(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown11(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown12(IN uint64_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown13(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown14(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown15(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown16(IN uint64_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown17(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown18(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown19(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown2(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown20(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown21(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown22(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown23(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown24(IN uint64_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown3(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown4(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown5(IN uint64_t _0, IN uint32_t _1, IN uint32_t _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown6(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown7(IN uint64_t _0, IN uint32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown8(IN uint64_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IUser::Unknown9(IN uint64_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nfp::detail::IUserManager::Unknown0(OUT IUnknown * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::nifm::detail {
	class IGeneralService {
	public:
		IGeneralService();
		uint32_t ConfirmSystemAvailability();
		uint32_t CreateRequest(IN int32_t _0, OUT nn::nifm::detail::IRequest * _1);
		uint32_t CreateScanRequest(OUT nn::nifm::detail::IScanRequest * _0);
		uint32_t CreateTemporaryNetworkProfile(IN nn::nifm::detail::sf::NetworkProfileData * _0, guint _0_size, OUT nn::util::Uuid& _1, OUT nn::nifm::detail::INetworkProfile * _2);
		uint32_t EnumerateNetworkInterfaces(IN uint32_t _0, OUT int32_t& _1, OUT nn::nifm::detail::sf::NetworkInterfaceInfo * _2, guint _2_size);
		uint32_t EnumerateNetworkProfiles(IN uint8_t _0, OUT int32_t& _1, OUT nn::nifm::detail::sf::NetworkProfileBasicInfo * _2, guint _2_size);
		uint32_t GetClientId(OUT nn::nifm::ClientId * _0, guint _0_size);
		uint32_t GetCurrentAccessPoint(OUT nn::nifm::detail::sf::AccessPointData * _0, guint _0_size);
		uint32_t GetCurrentIpAddress(OUT nn::nifm::IpV4Address& _0);
		uint32_t GetCurrentIpConfigInfo(OUT nn::nifm::IpAddressSetting& _0, OUT nn::nifm::DnsSetting& _1);
		uint32_t GetCurrentNetworkProfile(OUT nn::nifm::detail::sf::NetworkProfileData * _0, guint _0_size);
		uint32_t GetDefaultIpSetting(OUT nn::nifm::IpSettingData * _0, guint _0_size);
		uint32_t GetInternetConnectionStatus(OUT nn::nifm::detail::sf::InternetConnectionStatus& _0);
		uint32_t GetNetworkProfile(IN nn::util::Uuid _0, OUT nn::nifm::detail::sf::NetworkProfileData * _1, guint _1_size);
		uint32_t GetScanData(OUT int32_t& _0, OUT nn::nifm::detail::sf::AccessPointData * _1, guint _1_size);
		uint32_t GetSsidListVersion(OUT nn::nifm::SsidListVersion& _0);
		uint32_t GetTelemetorySystemEventReadableHandle(OUT KObject * _0);
		uint32_t GetTelemetryInfo(OUT nn::nifm::TelemetryInfo * _0, guint _0_size);
		uint32_t IsAnyForegroundRequestAccepted(OUT bool& _0);
		uint32_t IsAnyInternetRequestAccepted(IN nn::nifm::ClientId * _0, guint _0_size, OUT bool& _1);
		uint32_t IsEthernetCommunicationEnabled(OUT bool& _0);
		uint32_t IsWirelessCommunicationEnabled(OUT bool& _0);
		uint32_t PutToSleep();
		uint32_t RemoveNetworkProfile(IN nn::util::Uuid _0);
		uint32_t SetDefaultIpSetting(IN nn::nifm::IpSettingData * _0, guint _0_size);
		uint32_t SetEthernetCommunicationEnabled(IN bool _0);
		uint32_t SetEthernetCommunicationEnabledForTest(IN bool _0);
		uint32_t SetExclusiveClient(IN nn::nifm::ClientId * _0, guint _0_size);
		uint32_t SetNetworkProfile(IN nn::nifm::detail::sf::NetworkProfileData * _0, guint _0_size, OUT nn::util::Uuid& _1);
		uint32_t SetWirelessCommunicationEnabled(IN bool _0);
		uint32_t SetWirelessCommunicationEnabledForTest(IN bool _0);
		uint32_t WakeUp();
	};
	class INetworkProfile {
	public:
		INetworkProfile();
		uint32_t Persist(OUT nn::util::Uuid& _0);
		uint32_t PersistOld(IN nn::util::Uuid _0, OUT nn::util::Uuid& _1);
		uint32_t Update(IN nn::nifm::detail::sf::NetworkProfileData * _0, guint _0_size, OUT nn::util::Uuid& _1);
	};
	class IRequest {
	public:
		IRequest();
		uint32_t Cancel();
		uint32_t GetAdditionalInfo(OUT uint32_t& _0, OUT nn::nifm::AdditionalInfo * _1, guint _1_size);
		uint32_t GetAppletInfo(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t GetRequestState(OUT int32_t& _0);
		uint32_t GetRequirement(OUT nn::nifm::Requirement& _0);
		uint32_t GetResult();
		uint32_t GetRevision(OUT uint32_t& _0);
		uint32_t GetSystemEventReadableHandles(OUT KObject * _0, OUT KObject * _1);
		uint32_t RegisterSocketDescriptor(IN int32_t _0);
		uint32_t SetConnectionConfirmationOption(IN int8_t _0);
		uint32_t SetGreedy(IN bool _0);
		uint32_t SetInstant(IN bool _0);
		uint32_t SetKeptInSleep(IN bool _0);
		uint32_t SetNetworkProfileId(IN nn::util::Uuid _0);
		uint32_t SetPersistent(IN bool _0);
		uint32_t SetPriority(IN uint8_t _0);
		uint32_t SetRawPriority(IN uint8_t _0);
		uint32_t SetRejectable(IN bool _0);
		uint32_t SetRequirement(IN nn::nifm::Requirement _0);
		uint32_t SetRequirementByRevision(IN uint32_t _0);
		uint32_t SetRequirementPreset(IN int32_t _0);
		uint32_t SetSharable(IN bool _0);
		uint32_t SetSustainable(IN bool _0, IN uint8_t _1);
		uint32_t Submit();
		uint32_t UnregisterSocketDescriptor(IN int32_t _0);
	};
	class IScanRequest {
	public:
		IScanRequest();
		uint32_t GetResult();
		uint32_t GetSystemEventReadableHandle(OUT KObject * _0);
		uint32_t IsProcessing(OUT bool& _0);
		uint32_t Submit();
	};
	class IStaticService {
	public:
		IStaticService();
		uint32_t CreateGeneralService(IN uint64_t _0, IN gpid _1, OUT nn::nifm::detail::IGeneralService * _2);
		uint32_t CreateGeneralServiceOld(OUT nn::nifm::detail::IGeneralService * _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::nifm::detail::IGeneralService::ConfirmSystemAvailability() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::CreateRequest(IN int32_t _0, OUT nn::nifm::detail::IRequest * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::nifm::detail::IRequest(resp.move_handles[0]);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::CreateScanRequest(OUT nn::nifm::detail::IScanRequest * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::nifm::detail::IScanRequest(resp.move_handles[0]);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::CreateTemporaryNetworkProfile(IN nn::nifm::detail::sf::NetworkProfileData * _0, guint _0_size, OUT nn::util::Uuid& _1, OUT nn::nifm::detail::INetworkProfile * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_2 OMG = new nn::nifm::detail::INetworkProfile(resp.move_handles[0]);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::EnumerateNetworkInterfaces(IN uint32_t _0, OUT int32_t& _1, OUT nn::nifm::detail::sf::NetworkInterfaceInfo * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::EnumerateNetworkProfiles(IN uint8_t _0, OUT int32_t& _1, OUT nn::nifm::detail::sf::NetworkProfileBasicInfo * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetClientId(OUT nn::nifm::ClientId * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetCurrentAccessPoint(OUT nn::nifm::detail::sf::AccessPointData * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetCurrentIpAddress(OUT nn::nifm::IpV4Address& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetCurrentIpConfigInfo(OUT nn::nifm::IpAddressSetting& _0, OUT nn::nifm::DnsSetting& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::nifm::IpAddressSetting>(8);
	auto temp2 = resp.getDataPointer<nn::nifm::DnsSetting>(0x15);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetCurrentNetworkProfile(OUT nn::nifm::detail::sf::NetworkProfileData * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetDefaultIpSetting(OUT nn::nifm::IpSettingData * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetInternetConnectionStatus(OUT nn::nifm::detail::sf::InternetConnectionStatus& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::nifm::detail::sf::InternetConnectionStatus>(9);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetNetworkProfile(IN nn::util::Uuid _0, OUT nn::nifm::detail::sf::NetworkProfileData * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetScanData(OUT int32_t& _0, OUT nn::nifm::detail::sf::AccessPointData * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetSsidListVersion(OUT nn::nifm::SsidListVersion& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetTelemetorySystemEventReadableHandle(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::GetTelemetryInfo(OUT nn::nifm::TelemetryInfo * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::IsAnyForegroundRequestAccepted(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::IsAnyInternetRequestAccepted(IN nn::nifm::ClientId * _0, guint _0_size, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::IsEthernetCommunicationEnabled(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::IsWirelessCommunicationEnabled(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::PutToSleep() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::RemoveNetworkProfile(IN nn::util::Uuid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::SetDefaultIpSetting(IN nn::nifm::IpSettingData * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::SetEthernetCommunicationEnabled(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::SetEthernetCommunicationEnabledForTest(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::SetExclusiveClient(IN nn::nifm::ClientId * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::SetNetworkProfile(IN nn::nifm::detail::sf::NetworkProfileData * _0, guint _0_size, OUT nn::util::Uuid& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::SetWirelessCommunicationEnabled(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::SetWirelessCommunicationEnabledForTest(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IGeneralService::WakeUp() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::INetworkProfile::Persist(OUT nn::util::Uuid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::INetworkProfile::PersistOld(IN nn::util::Uuid _0, OUT nn::util::Uuid& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::INetworkProfile::Update(IN nn::nifm::detail::sf::NetworkProfileData * _0, guint _0_size, OUT nn::util::Uuid& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IRequest::Cancel() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::GetAdditionalInfo(OUT uint32_t& _0, OUT nn::nifm::AdditionalInfo * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IRequest::GetAppletInfo(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nifm::detail::IRequest::GetRequestState(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::GetRequirement(OUT nn::nifm::Requirement& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::nifm::Requirement>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::GetResult() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::GetRevision(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::GetSystemEventReadableHandles(OUT KObject * _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	shared_ptr<KObject> temp2;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	if(temp2 != nullptr)
		resp.copy(1, ctu->newHandle(temp2));
	return ret;
}
uint32_t nn::nifm::detail::IRequest::RegisterSocketDescriptor(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetConnectionConfirmationOption(IN int8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetGreedy(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetInstant(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetKeptInSleep(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetNetworkProfileId(IN nn::util::Uuid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetPersistent(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetPriority(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetRawPriority(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetRejectable(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetRequirement(IN nn::nifm::Requirement _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetRequirementByRevision(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetRequirementPreset(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetSharable(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::SetSustainable(IN bool _0, IN uint8_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::Submit() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IRequest::UnregisterSocketDescriptor(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IScanRequest::GetResult() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IScanRequest::GetSystemEventReadableHandle(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::nifm::detail::IScanRequest::IsProcessing(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IScanRequest::Submit() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nifm::detail::IStaticService::CreateGeneralService(IN uint64_t _0, IN gpid _1, OUT nn::nifm::detail::IGeneralService * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::nifm::detail::IGeneralService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::nifm::detail::IStaticService::CreateGeneralServiceOld(OUT nn::nifm::detail::IGeneralService * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::nifm::detail::IGeneralService(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::nim::detail {
	class IAsyncData {
	public:
		IAsyncData();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
	};
	class IAsyncProgressResult {
	public:
		IAsyncProgressResult();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
	};
	class IAsyncResult {
	public:
		IAsyncResult();
		uint32_t Unknown0();
		uint32_t Unknown1();
	};
	class IAsyncValue {
	public:
		IAsyncValue();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
	};
	class INetworkInstallManager {
	public:
		INetworkInstallManager();
		uint32_t Unknown2(IN uint8_t * _0, guint _0_size, OUT uint64_t& _1, OUT uint64_t& _2);
		uint32_t Unknown40(IN uint8_t * _0, guint _0_size, OUT uint64_t& _1, OUT uint64_t& _2);
		uint32_t Unknown8(OUT uint64_t& _0, OUT uint64_t& _1);
	};
	class IShopServiceManager {
	public:
		IShopServiceManager();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::nim::detail::IAsyncData::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncData::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncData::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncData::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncData::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncProgressResult::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncProgressResult::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncProgressResult::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncResult::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncResult::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncValue::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncValue::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::IAsyncValue::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nim::detail::INetworkInstallManager::Unknown2(IN uint8_t * _0, guint _0_size, OUT uint64_t& _1, OUT uint64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nim::detail::INetworkInstallManager::Unknown40(IN uint8_t * _0, guint _0_size, OUT uint64_t& _1, OUT uint64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nim::detail::INetworkInstallManager::Unknown8(OUT uint64_t& _0, OUT uint64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::npns {
	class INpnsSystem {
	public:
		INpnsSystem();
		uint32_t SetInterfaceVersion(OUT KObject * _0);
		uint32_t Unknown103(OUT KObject * _0);
		uint32_t Unknown7(OUT KObject * _0);
	};
	class INpnsUser {
	public:
		INpnsUser();
		uint32_t Unknown1();
		uint32_t Unknown101();
		uint32_t Unknown102();
		uint32_t Unknown103();
		uint32_t Unknown104();
		uint32_t Unknown111();
		uint32_t Unknown2();
		uint32_t Unknown21();
		uint32_t Unknown23();
		uint32_t Unknown25();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown7();
	};
	class Weird {
	public:
		Weird();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::npns::INpnsSystem::SetInterfaceVersion(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::npns::INpnsSystem::Unknown103(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::npns::INpnsSystem::Unknown7(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown101() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown102() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown103() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown104() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown111() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown21() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown23() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown25() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::npns::INpnsUser::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::ns::detail {
	class IAccountProxyInterface {
	public:
		IAccountProxyInterface();
		uint32_t Unknown0();
	};
	class IApplicationManagerInterface {
	public:
		IApplicationManagerInterface();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown100();
		uint32_t Unknown1000();
		uint32_t Unknown1001();
		uint32_t Unknown1002();
		uint32_t Unknown101();
		uint32_t Unknown102();
		uint32_t Unknown11();
		uint32_t Unknown1200();
		uint32_t Unknown1300();
		uint32_t Unknown1301();
		uint32_t Unknown1302();
		uint32_t Unknown1303();
		uint32_t Unknown1304();
		uint32_t Unknown1400();
		uint32_t Unknown1500();
		uint32_t Unknown1501();
		uint32_t Unknown1502();
		uint32_t Unknown1504();
		uint32_t Unknown1505();
		uint32_t Unknown16();
		uint32_t Unknown1600();
		uint32_t Unknown1601();
		uint32_t Unknown17();
		uint32_t Unknown1700();
		uint32_t Unknown1701();
		uint32_t Unknown1702();
		uint32_t Unknown1800();
		uint32_t Unknown1801();
		uint32_t Unknown1802();
		uint32_t Unknown1803();
		uint32_t Unknown19();
		uint32_t Unknown1900();
		uint32_t Unknown2();
		uint32_t Unknown200();
		uint32_t Unknown201();
		uint32_t Unknown21();
		uint32_t Unknown210();
		uint32_t Unknown22();
		uint32_t Unknown220();
		uint32_t Unknown23();
		uint32_t Unknown26();
		uint32_t Unknown27();
		uint32_t Unknown3();
		uint32_t Unknown30();
		uint32_t Unknown300();
		uint32_t Unknown301();
		uint32_t Unknown302();
		uint32_t Unknown303();
		uint32_t Unknown304();
		uint32_t Unknown305();
		uint32_t Unknown306();
		uint32_t Unknown307();
		uint32_t Unknown31();
		uint32_t Unknown32();
		uint32_t Unknown33();
		uint32_t Unknown35();
		uint32_t Unknown36();
		uint32_t Unknown37();
		uint32_t Unknown38();
		uint32_t Unknown39();
		uint32_t Unknown4();
		uint32_t Unknown40();
		uint32_t Unknown400();
		uint32_t Unknown401();
		uint32_t Unknown402();
		uint32_t Unknown403();
		uint32_t Unknown404();
		uint32_t Unknown405();
		uint32_t Unknown41();
		uint32_t Unknown42();
		uint32_t Unknown43();
		uint32_t Unknown44();
		uint32_t Unknown45();
		uint32_t Unknown46();
		uint32_t Unknown47();
		uint32_t Unknown48();
		uint32_t Unknown49();
		uint32_t Unknown5();
		uint32_t Unknown502();
		uint32_t Unknown503();
		uint32_t Unknown504();
		uint32_t Unknown505();
		uint32_t Unknown506();
		uint32_t Unknown507();
		uint32_t Unknown508();
		uint32_t Unknown52();
		uint32_t Unknown53();
		uint32_t Unknown54();
		uint32_t Unknown55();
		uint32_t Unknown56();
		uint32_t Unknown57();
		uint32_t Unknown58();
		uint32_t Unknown59();
		uint32_t Unknown6();
		uint32_t Unknown60();
		uint32_t Unknown600();
		uint32_t Unknown601();
		uint32_t Unknown602();
		uint32_t Unknown603();
		uint32_t Unknown604();
		uint32_t Unknown605();
		uint32_t Unknown606();
		uint32_t Unknown61();
		uint32_t Unknown62();
		uint32_t Unknown63();
		uint32_t Unknown64();
		uint32_t Unknown65();
		uint32_t Unknown66();
		uint32_t Unknown67();
		uint32_t Unknown68();
		uint32_t Unknown69();
		uint32_t Unknown7();
		uint32_t Unknown70();
		uint32_t Unknown700();
		uint32_t Unknown701();
		uint32_t Unknown702();
		uint32_t Unknown703();
		uint32_t Unknown704();
		uint32_t Unknown705();
		uint32_t Unknown71();
		uint32_t Unknown8();
		uint32_t Unknown80();
		uint32_t Unknown800();
		uint32_t Unknown801();
		uint32_t Unknown802();
		uint32_t Unknown81();
		uint32_t Unknown82();
		uint32_t Unknown9();
		uint32_t Unknown900();
		uint32_t Unknown901();
		uint32_t Unknown902();
		uint32_t Unknown903();
		uint32_t Unknown904();
		uint32_t Unknown905();
		uint32_t Unknown906();
		uint32_t Unknown907();
		uint32_t Unknown908();
		uint32_t Unknown909();
	};
	class IAsyncResult {
	public:
		IAsyncResult();
		uint32_t Unknown0();
		uint32_t Unknown1();
	};
	class IAsyncValue {
	public:
		IAsyncValue();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
	};
	class IContentManagementInterface {
	public:
		IContentManagementInterface();
		uint32_t Unknown11();
		uint32_t Unknown43();
		uint32_t Unknown47();
		uint32_t Unknown48();
		uint32_t Unknown600();
		uint32_t Unknown601();
		uint32_t Unknown605();
		uint32_t Unknown607();
	};
	class IDevelopInterface {
	public:
		IDevelopInterface();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
	class IDocumentInterface {
	public:
		IDocumentInterface();
		uint32_t Unknown21();
		uint32_t Unknown23();
	};
	class IDownloadTaskInterface {
	public:
		IDownloadTaskInterface();
		uint32_t Unknown701();
		uint32_t Unknown702();
		uint32_t Unknown703();
		uint32_t Unknown704();
		uint32_t Unknown705();
	};
	class IFactoryResetInterface {
	public:
		IFactoryResetInterface();
		uint32_t Unknown100();
		uint32_t Unknown101();
		uint32_t Unknown102();
	};
	class IGameCardStopper {
	public:
		IGameCardStopper();
	};
	class IProgressAsyncResult {
	public:
		IProgressAsyncResult();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
	};
	class IProgressMonitorForDeleteUserSaveDataAll {
	public:
		IProgressMonitorForDeleteUserSaveDataAll();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown2();
	};
	class IRequestServerStopper {
	public:
		IRequestServerStopper();
	};
	class IServiceGetterInterface {
	public:
		IServiceGetterInterface();
		uint32_t Unknown7994();
		uint32_t Unknown7995();
		uint32_t Unknown7996();
		uint32_t Unknown7997();
		uint32_t Unknown7998();
		uint32_t Unknown7999();
	};
	class ISystemUpdateControl {
	public:
		ISystemUpdateControl();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
	class ISystemUpdateInterface {
	public:
		ISystemUpdateInterface();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown14();
		uint32_t Unknown15();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown9();
	};
	class IVulnerabilityManagerInterface {
	public:
		IVulnerabilityManagerInterface();
		uint32_t Unknown1200();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::ns::detail::IAccountProxyInterface::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown100() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1000() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1001() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1002() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown101() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown102() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1200() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1300() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1301() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1302() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1303() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1304() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1400() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1500() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1501() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1502() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1504() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1505() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown16() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1600() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1601() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown17() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1700() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1701() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1702() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1800() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1801() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1802() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1803() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown19() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown1900() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown200() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown201() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown21() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown210() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown22() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown220() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown23() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown26() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown27() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown30() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown300() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown301() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown302() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown303() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown304() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown305() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown306() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown307() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown31() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown32() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown33() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown35() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown36() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown37() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown38() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown39() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown40() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown400() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown401() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown402() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown403() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown404() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown405() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown41() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown42() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown43() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown44() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown45() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown46() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown47() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown48() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown49() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown502() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown503() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown504() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown505() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown506() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown507() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown508() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown52() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown53() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown54() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown55() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown56() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown57() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown58() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown59() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown60() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown600() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown601() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown602() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown603() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown604() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown605() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown606() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown61() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown62() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown63() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown64() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown65() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown66() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown67() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown68() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown69() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown70() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown700() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown701() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown702() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown703() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown704() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown705() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown71() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown80() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown800() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown801() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown802() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown81() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown82() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown900() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown901() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown902() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown903() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown904() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown905() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown906() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown907() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown908() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IApplicationManagerInterface::Unknown909() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IAsyncResult::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IAsyncResult::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IAsyncValue::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IAsyncValue::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IAsyncValue::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IContentManagementInterface::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IContentManagementInterface::Unknown43() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IContentManagementInterface::Unknown47() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IContentManagementInterface::Unknown48() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IContentManagementInterface::Unknown600() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IContentManagementInterface::Unknown601() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IContentManagementInterface::Unknown605() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IContentManagementInterface::Unknown607() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDevelopInterface::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDevelopInterface::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDevelopInterface::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDevelopInterface::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDevelopInterface::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDevelopInterface::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDevelopInterface::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDevelopInterface::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDevelopInterface::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDocumentInterface::Unknown21() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDocumentInterface::Unknown23() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDownloadTaskInterface::Unknown701() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDownloadTaskInterface::Unknown702() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDownloadTaskInterface::Unknown703() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDownloadTaskInterface::Unknown704() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IDownloadTaskInterface::Unknown705() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IFactoryResetInterface::Unknown100() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IFactoryResetInterface::Unknown101() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IFactoryResetInterface::Unknown102() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IProgressAsyncResult::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IProgressAsyncResult::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IProgressAsyncResult::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IProgressAsyncResult::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IProgressMonitorForDeleteUserSaveDataAll::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IProgressMonitorForDeleteUserSaveDataAll::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IProgressMonitorForDeleteUserSaveDataAll::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IProgressMonitorForDeleteUserSaveDataAll::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IServiceGetterInterface::Unknown7994() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IServiceGetterInterface::Unknown7995() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IServiceGetterInterface::Unknown7996() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IServiceGetterInterface::Unknown7997() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IServiceGetterInterface::Unknown7998() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IServiceGetterInterface::Unknown7999() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateControl::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown14() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown15() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::ISystemUpdateInterface::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ns::detail::IVulnerabilityManagerInterface::Unknown1200() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::nsd::detail {
	class IManager {
	public:
		IManager();
		uint32_t Unknown10(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown11(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown12(OUT uint128_t& _0);
		uint32_t Unknown13(IN uint32_t _0);
		uint32_t Unknown14(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown20(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown21(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown30(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown31(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown40(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown41(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown42(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown43(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown50(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown60(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown61(IN uint8_t * _0, guint _0_size);
		uint32_t Unknown62();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::nsd::detail::IManager::Unknown10(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown11(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown12(OUT uint128_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown13(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown14(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown20(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x15, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x16, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown21(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x15, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x16, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown30(IN uint8_t * _0, guint _0_size, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x15, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x16, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown31(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x15, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x16, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown40(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown41(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown42(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown43(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown50(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown60(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown61(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x15, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::nsd::detail::IManager::Unknown62() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::ntc::detail::service {
	class IEnsureNetworkClockAvailabilityService {
	public:
		IEnsureNetworkClockAvailabilityService();
		uint32_t Unknown0();
		uint32_t Unknown1(OUT KObject * _0);
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4(OUT uint8_t& _0);
		uint32_t Unknown5(OUT uint64_t& _0);
	};
	class IStaticService {
	public:
		IStaticService();
		uint32_t Unknown0(IN uint32_t _0, IN uint32_t _1, OUT IUnknown * _2);
		uint32_t Unknown100();
		uint32_t Unknown101();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::ntc::detail::service::IEnsureNetworkClockAvailabilityService::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ntc::detail::service::IEnsureNetworkClockAvailabilityService::Unknown1(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::ntc::detail::service::IEnsureNetworkClockAvailabilityService::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ntc::detail::service::IEnsureNetworkClockAvailabilityService::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ntc::detail::service::IEnsureNetworkClockAvailabilityService::Unknown4(OUT uint8_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ntc::detail::service::IEnsureNetworkClockAvailabilityService::Unknown5(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ntc::detail::service::IStaticService::Unknown0(IN uint32_t _0, IN uint32_t _1, OUT IUnknown * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::ntc::detail::service::IStaticService::Unknown100() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ntc::detail::service::IStaticService::Unknown101() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::omm::detail {
	class IOperationModeManager {
	public:
		IOperationModeManager();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown14();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::omm::detail::IOperationModeManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown14() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::omm::detail::IOperationModeManager::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::ovln {
	class IReceiver {
	public:
		IReceiver();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
	};
	class IReceiverService {
	public:
		IReceiverService();
		uint32_t Unknown0();
	};
	class ISender {
	public:
		ISender();
		uint32_t Unknown0(IN uint64_t unk1, IN uint64_t unk2, IN uint64_t unk3, IN uint64_t unk4, IN uint64_t unk5, IN uint64_t unk6, IN uint64_t unk7, IN uint64_t unk8, IN uint64_t unk9, IN uint64_t unk10, IN uint64_t unk11, IN uint64_t unk12, IN uint64_t unk13, IN uint64_t unk14, IN uint64_t unk15, IN uint64_t unk16, IN uint64_t unk17);
	};
	class ISenderService {
	public:
		ISenderService();
		uint32_t Unknown0();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::ovln::IReceiver::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ovln::IReceiver::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ovln::IReceiver::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ovln::IReceiver::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ovln::IReceiver::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ovln::IReceiverService::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ovln::ISender::Unknown0(IN uint64_t unk1, IN uint64_t unk2, IN uint64_t unk3, IN uint64_t unk4, IN uint64_t unk5, IN uint64_t unk6, IN uint64_t unk7, IN uint64_t unk8, IN uint64_t unk9, IN uint64_t unk10, IN uint64_t unk11, IN uint64_t unk12, IN uint64_t unk13, IN uint64_t unk14, IN uint64_t unk15, IN uint64_t unk16, IN uint64_t unk17) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ovln::ISenderService::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::pcie::detail {
	class IManager {
	public:
		IManager();
		uint32_t Unknown0();
		uint32_t Unknown1();
	};
	class ISession {
	public:
		ISession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown14();
		uint32_t Unknown15();
		uint32_t Unknown16();
		uint32_t Unknown17();
		uint32_t Unknown18();
		uint32_t Unknown19();
		uint32_t Unknown2();
		uint32_t Unknown20();
		uint32_t Unknown21();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::pcie::detail::IManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::IManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown14() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown15() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown16() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown17() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown18() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown19() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown20() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown21() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcie::detail::ISession::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::pctl::detail::ipc {
	class IParentalControlService {
	public:
		IParentalControlService();
		uint32_t AddToFreeCommunicationApplicationList(IN nn::ncm::ApplicationId _0);
		uint32_t AuthorizePairingAsync(IN nn::pctl::detail::PairingInfoBase _0, OUT nn::pctl::detail::AsyncData& _1, OUT KObject * _2);
		uint32_t CancelNetworkRequest();
		uint32_t CheckFreeCommunicationPermission();
		uint32_t CheckMasterKey(IN nn::pctl::InquiryCode _0, IN int8_t * _1, guint _1_size, OUT bool& _2);
		uint32_t ClearFreeCommunicationApplicationListForDebug();
		uint32_t ClearUnlinkedEvent();
		uint32_t ConfirmLaunchApplicationPermission(IN bool _0, IN nn::ncm::ApplicationId _1, IN int8_t * _2, guint _2_size);
		uint32_t ConfirmResumeApplicationPermission(IN bool _0, IN nn::ncm::ApplicationId _1, IN int8_t * _2, guint _2_size);
		uint32_t ConfirmSnsPostPermission();
		uint32_t ConfirmSystemSettingsPermission();
		uint32_t DeleteFromFreeCommunicationApplicationListForDebug(IN nn::ncm::ApplicationId _0);
		uint32_t DeletePairing();
		uint32_t DeleteSettings();
		uint32_t DisableAllFeatures(OUT bool& _0);
		uint32_t DisableFeaturesForReset();
		uint32_t EnterRestrictedSystemSettings();
		uint32_t FinishAuthorizePairing(IN nn::pctl::detail::AsyncData _0, OUT nn::pctl::detail::PairingInfoBase& _1);
		uint32_t FinishGetAccountMiiImage(IN nn::pctl::detail::AsyncData _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t FinishGetAccountMiiImageContentType(IN nn::pctl::detail::AsyncData _0, OUT uint32_t& _1, OUT int8_t * _2, guint _2_size);
		uint32_t FinishRequestPairing(IN nn::pctl::detail::AsyncData _0, OUT nn::pctl::detail::PairingInfoBase& _1);
		uint32_t FinishRetrievePairingInfo(IN nn::pctl::detail::AsyncData _0, OUT nn::pctl::detail::PairingInfoBase& _1);
		uint32_t FinishSynchronizeParentalControlSettings(IN nn::pctl::detail::AsyncData _0);
		uint32_t FinishSynchronizeParentalControlSettingsWithLastUpdated(IN nn::pctl::detail::AsyncData _0, OUT nn::time::PosixTime& _1);
		uint32_t FinishUnlinkPairing(IN bool _0, IN nn::pctl::detail::AsyncData _1);
		uint32_t GenerateInquiryCode(OUT nn::pctl::InquiryCode& _0);
		uint32_t GetAccountMiiImageAsync(IN nn::pctl::detail::PairingAccountInfoBase _0, OUT nn::pctl::detail::AsyncData& _1, OUT uint32_t& _2, OUT KObject * _3, OUT uint8_t * _4, guint _4_size);
		uint32_t GetAccountMiiImageContentTypeAsync(IN nn::pctl::detail::PairingAccountInfoBase _0, OUT nn::pctl::detail::AsyncData& _1, OUT uint32_t& _2, OUT KObject * _3, OUT int8_t * _4, guint _4_size);
		uint32_t GetAccountNickname(IN nn::pctl::detail::PairingAccountInfoBase _0, OUT uint32_t& _1, OUT int8_t * _2, guint _2_size);
		uint32_t GetAccountState(IN nn::pctl::detail::PairingAccountInfoBase _0, OUT int32_t& _1);
		uint32_t GetCurrentSettings(OUT nn::pctl::SafetyLevelSettings& _0);
		uint32_t GetDefaultRatingOrganization(OUT int32_t& _0);
		uint32_t GetFreeCommunicationApplicationList(IN int32_t _0, OUT int32_t& _1, OUT nn::pctl::FreeCommunicationApplicationInfo * _2, guint _2_size);
		uint32_t GetFreeCommunicationApplicationListCount(OUT int32_t& _0);
		uint32_t GetPairingAccountInfo(IN nn::pctl::detail::PairingInfoBase _0, OUT nn::pctl::detail::PairingAccountInfoBase& _1);
		uint32_t GetPinCodeChangedEvent(OUT KObject * _0);
		uint32_t GetPinCodeLength(OUT int32_t& _0);
		uint32_t GetPlayTimerEventToRequestSuspension(OUT KObject * _0);
		uint32_t GetPlayTimerRemainingTime(OUT nn::TimeSpanType& _0);
		uint32_t GetPlayTimerSettings(OUT nn::pctl::PlayTimerSettings& _0);
		uint32_t GetPlayTimerSpentTimeForTest(OUT nn::TimeSpanType& _0);
		uint32_t GetRestrictedFeatures(OUT int32_t& _0);
		uint32_t GetSafetyLevel(OUT int32_t& _0);
		uint32_t GetSafetyLevelSettings(IN int32_t _0, OUT nn::pctl::SafetyLevelSettings& _1);
		uint32_t GetSettingsLastUpdated(OUT nn::time::PosixTime& _0);
		uint32_t GetSynchronizationEvent(OUT KObject * _0);
		uint32_t GetUnlinkedEvent(OUT KObject * _0);
		uint32_t IsAllFeaturesDisabled(OUT bool& _0, OUT bool& _1);
		uint32_t IsPairingActive(OUT bool& _0);
		uint32_t IsPlayTimerEnabled(OUT bool& _0);
		uint32_t IsRestrictedByPlayTimer(OUT bool& _0);
		uint32_t IsRestrictedSystemSettingsEntered(OUT bool& _0);
		uint32_t IsRestrictionEnabled(OUT bool& _0);
		uint32_t IsRestrictionTemporaryUnlocked(OUT bool& _0);
		uint32_t LeaveRestrictedSystemSettings();
		uint32_t NotifyApplicationDownloadStarted(IN nn::ncm::ApplicationId _0);
		uint32_t NotifyWrongPinCodeInputManyTimes();
		uint32_t PostEnableAllFeatures(OUT bool& _0);
		uint32_t RequestPairingAsync(IN int8_t * _0, guint _0_size, OUT nn::pctl::detail::AsyncData& _1, OUT KObject * _2);
		uint32_t RetrievePairingInfoAsync(OUT nn::pctl::detail::AsyncData& _0, OUT KObject * _1);
		uint32_t RevertRestrictedSystemSettingsEntered();
		uint32_t RevertRestrictionTemporaryUnlocked();
		uint32_t SetCustomSafetyLevelSettings(IN nn::pctl::SafetyLevelSettings _0);
		uint32_t SetDefaultRatingOrganization(IN int32_t _0);
		uint32_t SetPinCode(IN int8_t * _0, guint _0_size);
		uint32_t SetPlayTimerSettingsForDebug(IN nn::pctl::PlayTimerSettings _0);
		uint32_t SetSafetyLevel(IN int32_t _0);
		uint32_t StartPlayTimer();
		uint32_t StopPlayTimer();
		uint32_t SynchronizeParentalControlSettingsAsync(OUT nn::pctl::detail::AsyncData& _0, OUT KObject * _1);
		uint32_t UnlinkPairingAsync(IN bool _0, OUT nn::pctl::detail::AsyncData& _1, OUT KObject * _2);
		uint32_t UnlockRestrictionTemporarily(IN int8_t * _0, guint _0_size);
		uint32_t UnlockSystemSettingsRestriction(IN int8_t * _0, guint _0_size);
		uint32_t UpdateFreeCommunicationApplicationList(IN nn::pctl::FreeCommunicationApplicationInfo * _0, guint _0_size);
	};
	class IParentalControlServiceFactory {
	public:
		IParentalControlServiceFactory();
		uint32_t CreateService(IN uint64_t _0, IN gpid _1, OUT nn::pctl::detail::ipc::IParentalControlService * _2);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::pctl::detail::ipc::IParentalControlService::AddToFreeCommunicationApplicationList(IN nn::ncm::ApplicationId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::AuthorizePairingAsync(IN nn::pctl::detail::PairingInfoBase _0, OUT nn::pctl::detail::AsyncData& _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::CancelNetworkRequest() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::CheckFreeCommunicationPermission() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::CheckMasterKey(IN nn::pctl::InquiryCode _0, IN int8_t * _1, guint _1_size, OUT bool& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::ClearFreeCommunicationApplicationListForDebug() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::ClearUnlinkedEvent() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::ConfirmLaunchApplicationPermission(IN bool _0, IN nn::ncm::ApplicationId _1, IN int8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::ConfirmResumeApplicationPermission(IN bool _0, IN nn::ncm::ApplicationId _1, IN int8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::ConfirmSnsPostPermission() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::ConfirmSystemSettingsPermission() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::DeleteFromFreeCommunicationApplicationListForDebug(IN nn::ncm::ApplicationId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::DeletePairing() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::DeleteSettings() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::DisableAllFeatures(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::DisableFeaturesForReset() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::EnterRestrictedSystemSettings() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::FinishAuthorizePairing(IN nn::pctl::detail::AsyncData _0, OUT nn::pctl::detail::PairingInfoBase& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::FinishGetAccountMiiImage(IN nn::pctl::detail::AsyncData _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::FinishGetAccountMiiImageContentType(IN nn::pctl::detail::AsyncData _0, OUT uint32_t& _1, OUT int8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::FinishRequestPairing(IN nn::pctl::detail::AsyncData _0, OUT nn::pctl::detail::PairingInfoBase& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::FinishRetrievePairingInfo(IN nn::pctl::detail::AsyncData _0, OUT nn::pctl::detail::PairingInfoBase& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::FinishSynchronizeParentalControlSettings(IN nn::pctl::detail::AsyncData _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::FinishSynchronizeParentalControlSettingsWithLastUpdated(IN nn::pctl::detail::AsyncData _0, OUT nn::time::PosixTime& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::FinishUnlinkPairing(IN bool _0, IN nn::pctl::detail::AsyncData _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GenerateInquiryCode(OUT nn::pctl::InquiryCode& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::pctl::InquiryCode>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetAccountMiiImageAsync(IN nn::pctl::detail::PairingAccountInfoBase _0, OUT nn::pctl::detail::AsyncData& _1, OUT uint32_t& _2, OUT KObject * _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	guint temp3;
	auto temp2 = req.getBuffer(6, 0, temp3);
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	ctu->cpu.writemem(temp2, temp4, temp3);
	delete[] temp4;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetAccountMiiImageContentTypeAsync(IN nn::pctl::detail::PairingAccountInfoBase _0, OUT nn::pctl::detail::AsyncData& _1, OUT uint32_t& _2, OUT KObject * _3, OUT int8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	guint temp3;
	auto temp2 = req.getBuffer(0xa, 0, temp3);
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	ctu->cpu.writemem(temp2, temp4, temp3);
	delete[] temp4;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetAccountNickname(IN nn::pctl::detail::PairingAccountInfoBase _0, OUT uint32_t& _1, OUT int8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetAccountState(IN nn::pctl::detail::PairingAccountInfoBase _0, OUT int32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetCurrentSettings(OUT nn::pctl::SafetyLevelSettings& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::pctl::SafetyLevelSettings>(9);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetDefaultRatingOrganization(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetFreeCommunicationApplicationList(IN int32_t _0, OUT int32_t& _1, OUT nn::pctl::FreeCommunicationApplicationInfo * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetFreeCommunicationApplicationListCount(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetPairingAccountInfo(IN nn::pctl::detail::PairingInfoBase _0, OUT nn::pctl::detail::PairingAccountInfoBase& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetPinCodeChangedEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetPinCodeLength(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetPlayTimerEventToRequestSuspension(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetPlayTimerRemainingTime(OUT nn::TimeSpanType& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetPlayTimerSettings(OUT nn::pctl::PlayTimerSettings& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::pctl::PlayTimerSettings>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetPlayTimerSpentTimeForTest(OUT nn::TimeSpanType& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetRestrictedFeatures(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetSafetyLevel(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetSafetyLevelSettings(IN int32_t _0, OUT nn::pctl::SafetyLevelSettings& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::pctl::SafetyLevelSettings>(9);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetSettingsLastUpdated(OUT nn::time::PosixTime& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetSynchronizationEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::GetUnlinkedEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::IsAllFeaturesDisabled(OUT bool& _0, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::IsPairingActive(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::IsPlayTimerEnabled(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::IsRestrictedByPlayTimer(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::IsRestrictedSystemSettingsEntered(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::IsRestrictionEnabled(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::IsRestrictionTemporaryUnlocked(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::LeaveRestrictedSystemSettings() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::NotifyApplicationDownloadStarted(IN nn::ncm::ApplicationId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::NotifyWrongPinCodeInputManyTimes() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::PostEnableAllFeatures(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::RequestPairingAsync(IN int8_t * _0, guint _0_size, OUT nn::pctl::detail::AsyncData& _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	shared_ptr<KObject> temp4;
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	if(temp4 != nullptr)
		resp.copy(0, ctu->newHandle(temp4));
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::RetrievePairingInfoAsync(OUT nn::pctl::detail::AsyncData& _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::RevertRestrictedSystemSettingsEntered() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::RevertRestrictionTemporaryUnlocked() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::SetCustomSafetyLevelSettings(IN nn::pctl::SafetyLevelSettings _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::SetDefaultRatingOrganization(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::SetPinCode(IN int8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::SetPlayTimerSettingsForDebug(IN nn::pctl::PlayTimerSettings _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::SetSafetyLevel(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::StartPlayTimer() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::StopPlayTimer() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::SynchronizeParentalControlSettingsAsync(OUT nn::pctl::detail::AsyncData& _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::UnlinkPairingAsync(IN bool _0, OUT nn::pctl::detail::AsyncData& _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::UnlockRestrictionTemporarily(IN int8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::UnlockSystemSettingsRestriction(IN int8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlService::UpdateFreeCommunicationApplicationList(IN nn::pctl::FreeCommunicationApplicationInfo * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::pctl::detail::ipc::IParentalControlServiceFactory::CreateService(IN uint64_t _0, IN gpid _1, OUT nn::pctl::detail::ipc::IParentalControlService * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::pctl::detail::ipc::IParentalControlService(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::pcv {
	class IArbitrationManager {
	public:
		IArbitrationManager();
		uint32_t ReleaseControl(IN int32_t _0);
	};
	class IImmediateManager {
	public:
		IImmediateManager();
		uint32_t SetClockRate(IN int32_t _0, IN uint32_t _1);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::pcv::IArbitrationManager::ReleaseControl(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::IImmediateManager::SetClockRate(IN int32_t _0, IN uint32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::pcv::detail {
	class IPcvService {
	public:
		IPcvService();
		uint32_t ChangeVoltage(IN nn::pcv::PowerControlTarget _0, IN int32_t _1);
		uint32_t Finalize();
		uint32_t GetClockRate(IN int32_t _0, OUT uint32_t& _1);
		uint32_t GetDvfsTable(IN int32_t _0, IN int32_t _1, OUT int32_t& _2, OUT uint32_t * _3, guint _3_size, OUT int32_t * _4, guint _4_size);
		uint32_t GetFuseInfo(IN int32_t _0, OUT int32_t& _1, OUT uint32_t * _2, guint _2_size);
		uint32_t GetModuleStateTable(IN int32_t _0, OUT int32_t& _1, OUT nn::pcv::ModuleState * _2, guint _2_size);
		uint32_t GetOscillatorClock(OUT uint32_t& _0);
		uint32_t GetPossibleClockRates(IN int32_t _0, IN int32_t _1, OUT int32_t& _2, OUT int32_t& _3, OUT uint32_t * _4, guint _4_size);
		uint32_t GetPowerClockInfoEvent(OUT KObject * _0);
		uint32_t GetPowerDomainStateTable(IN int32_t _0, OUT int32_t& _1, OUT nn::pcv::PowerDomainState * _2, guint _2_size);
		uint32_t GetState(IN int32_t _0, OUT nn::pcv::ModuleState& _1);
		uint32_t GetTemperatureThresholds(IN int32_t _0, OUT int32_t& _1, OUT nn::pcv::TemperatureThreshold * _2, guint _2_size);
		uint32_t GetVoltageEnabled(IN int32_t _0, OUT bool& _1);
		uint32_t GetVoltageRange(IN int32_t _0, OUT int32_t& _1, OUT int32_t& _2, OUT int32_t& _3);
		uint32_t GetVoltageValue(IN int32_t _0, OUT int32_t& _1);
		uint32_t Initialize();
		uint32_t IsInitialized(OUT bool& _0);
		uint32_t PowerOff(IN nn::pcv::PowerControlTarget _0);
		uint32_t PowerOn(IN nn::pcv::PowerControlTarget _0, IN int32_t _1);
		uint32_t SetClockEnabled(IN bool _0, IN int32_t _1);
		uint32_t SetClockRate(IN int32_t _0, IN uint32_t _1);
		uint32_t SetMinVClockRate(IN int32_t _0, IN uint32_t _1);
		uint32_t SetPowerEnabled(IN bool _0, IN int32_t _1);
		uint32_t SetReset(IN bool _0, IN int32_t _1);
		uint32_t SetTemperature(IN int32_t _0);
		uint32_t SetVoltageEnabled(IN bool _0, IN int32_t _1);
		uint32_t SetVoltageValue(IN int32_t _0, IN int32_t _1);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::pcv::detail::IPcvService::ChangeVoltage(IN nn::pcv::PowerControlTarget _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::Finalize() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetClockRate(IN int32_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetDvfsTable(IN int32_t _0, IN int32_t _1, OUT int32_t& _2, OUT uint32_t * _3, guint _3_size, OUT int32_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0xa, 1, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetFuseInfo(IN int32_t _0, OUT int32_t& _1, OUT uint32_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetModuleStateTable(IN int32_t _0, OUT int32_t& _1, OUT nn::pcv::ModuleState * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetOscillatorClock(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetPossibleClockRates(IN int32_t _0, IN int32_t _1, OUT int32_t& _2, OUT int32_t& _3, OUT uint32_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetPowerClockInfoEvent(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetPowerDomainStateTable(IN int32_t _0, OUT int32_t& _1, OUT nn::pcv::PowerDomainState * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetState(IN int32_t _0, OUT nn::pcv::ModuleState& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::pcv::ModuleState>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetTemperatureThresholds(IN int32_t _0, OUT int32_t& _1, OUT nn::pcv::TemperatureThreshold * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetVoltageEnabled(IN int32_t _0, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetVoltageRange(IN int32_t _0, OUT int32_t& _1, OUT int32_t& _2, OUT int32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::GetVoltageValue(IN int32_t _0, OUT int32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::Initialize() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::IsInitialized(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::PowerOff(IN nn::pcv::PowerControlTarget _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::PowerOn(IN nn::pcv::PowerControlTarget _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::SetClockEnabled(IN bool _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::SetClockRate(IN int32_t _0, IN uint32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::SetMinVClockRate(IN int32_t _0, IN uint32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::SetPowerEnabled(IN bool _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::SetReset(IN bool _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::SetTemperature(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::SetVoltageEnabled(IN bool _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pcv::detail::IPcvService::SetVoltageValue(IN int32_t _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::pdm::detail {
	class INotifyService {
	public:
		INotifyService();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1);
		uint32_t Unknown2(IN uint8_t _0);
		uint32_t Unknown3(IN uint8_t _0);
		uint32_t Unknown4();
		uint32_t Unknown5(IN uint8_t * _0, guint _0_size);
	};
	class IQueryService {
	public:
		IQueryService();
		uint32_t Unknown0(IN uint32_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown1(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown10(IN uint32_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown2(IN uint64_t _0, IN uint64_t _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t Unknown3(IN uint64_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown4(IN uint64_t _0, OUT uint64_t& _1, OUT uint64_t& _2, OUT uint64_t& _3, OUT uint64_t& _4, OUT uint64_t& _5);
		uint32_t Unknown5(IN uint64_t _0, IN uint64_t _1, IN uint64_t _2, OUT uint64_t& _3, OUT uint64_t& _4, OUT uint64_t& _5, OUT uint64_t& _6, OUT uint64_t& _7);
		uint32_t Unknown6(IN uint64_t _0, IN uint64_t _1, OUT uint64_t& _2, OUT uint64_t& _3, OUT uint64_t& _4, OUT uint64_t& _5, OUT uint64_t& _6);
		uint32_t Unknown7(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown8(IN uint32_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown9(OUT uint32_t& _0, OUT uint32_t& _1, OUT uint32_t& _2);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::pdm::detail::INotifyService::Unknown0(IN uint64_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pdm::detail::INotifyService::Unknown2(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pdm::detail::INotifyService::Unknown3(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pdm::detail::INotifyService::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pdm::detail::INotifyService::Unknown5(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::pdm::detail::IQueryService::Unknown0(IN uint32_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pdm::detail::IQueryService::Unknown1(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pdm::detail::IQueryService::Unknown10(IN uint32_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pdm::detail::IQueryService::Unknown2(IN uint64_t _0, IN uint64_t _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pdm::detail::IQueryService::Unknown3(IN uint64_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pdm::detail::IQueryService::Unknown4(IN uint64_t _0, OUT uint64_t& _1, OUT uint64_t& _2, OUT uint64_t& _3, OUT uint64_t& _4, OUT uint64_t& _5) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pdm::detail::IQueryService::Unknown5(IN uint64_t _0, IN uint64_t _1, IN uint64_t _2, OUT uint64_t& _3, OUT uint64_t& _4, OUT uint64_t& _5, OUT uint64_t& _6, OUT uint64_t& _7) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pdm::detail::IQueryService::Unknown6(IN uint64_t _0, IN uint64_t _1, OUT uint64_t& _2, OUT uint64_t& _3, OUT uint64_t& _4, OUT uint64_t& _5, OUT uint64_t& _6) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pdm::detail::IQueryService::Unknown7(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::pdm::detail::IQueryService::Unknown8(IN uint32_t _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::pdm::detail::IQueryService::Unknown9(OUT uint32_t& _0, OUT uint32_t& _1, OUT uint32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::pinmux {
	class IManager {
	public:
		IManager();
		uint32_t Unknown0();
	};
	class ISession {
	public:
		ISession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::pinmux::IManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pinmux::ISession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pinmux::ISession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pinmux::ISession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::pl::detail {
	class ISharedFontManager {
	public:
		ISharedFontManager();
		uint32_t Unknown0(IN uint32_t _0);
		uint32_t Unknown1(IN uint32_t _0, OUT uint32_t& _1);
		uint32_t Unknown2(IN uint32_t _0, OUT uint32_t& _1);
		uint32_t Unknown3(IN uint32_t _0, OUT uint32_t& _1);
		uint32_t Unknown4(OUT KObject * _0);
		uint32_t Unknown5(IN uint64_t _0, OUT uint8_t& _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size, OUT uint8_t * _4, guint _4_size, OUT uint8_t * _5, guint _5_size);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::pl::detail::ISharedFontManager::Unknown0(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pl::detail::ISharedFontManager::Unknown1(IN uint32_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pl::detail::ISharedFontManager::Unknown2(IN uint32_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pl::detail::ISharedFontManager::Unknown3(IN uint32_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pl::detail::ISharedFontManager::Unknown4(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::pl::detail::ISharedFontManager::Unknown5(IN uint64_t _0, OUT uint8_t& _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size, OUT uint8_t * _4, guint _4_size, OUT uint8_t * _5, guint _5_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 1, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(6, 2, temp8);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	ctu->cpu.writemem(temp7, temp9, temp8);
	delete[] temp9;
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::prepo::detail::ipc {
	class IPrepoService {
	public:
		IPrepoService();
		uint32_t ClearStorage();
		uint32_t GetStorageUsage(OUT int64_t& _0, OUT int64_t& _1);
		uint32_t GetTransmissionStatus(OUT int32_t& _0);
		uint32_t IsUserAgreementCheckEnabled(OUT bool& _0);
		uint32_t RequestImmediateTransmission();
		uint32_t SaveReport(IN uint64_t _0, IN gpid _1, IN int8_t * _2, guint _2_size, IN uint8_t * _3, guint _3_size);
		uint32_t SaveReportWithUser(IN nn::account::Uid _0, IN uint64_t _1, IN gpid _2, IN int8_t * _3, guint _3_size, IN uint8_t * _4, guint _4_size);
		uint32_t SaveSystemReport(IN nn::ApplicationId _0, IN int8_t * _1, guint _1_size, IN uint8_t * _2, guint _2_size);
		uint32_t SaveSystemReportWithUser(IN nn::account::Uid _0, IN nn::ApplicationId _1, IN int8_t * _2, guint _2_size, IN uint8_t * _3, guint _3_size);
		uint32_t SetUserAgreementCheckEnabled(IN bool _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::prepo::detail::ipc::IPrepoService::ClearStorage() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::prepo::detail::ipc::IPrepoService::GetStorageUsage(OUT int64_t& _0, OUT int64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::prepo::detail::ipc::IPrepoService::GetTransmissionStatus(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::prepo::detail::ipc::IPrepoService::IsUserAgreementCheckEnabled(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::prepo::detail::ipc::IPrepoService::RequestImmediateTransmission() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::prepo::detail::ipc::IPrepoService::SaveReport(IN uint64_t _0, IN gpid _1, IN int8_t * _2, guint _2_size, IN uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(5, 0, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::prepo::detail::ipc::IPrepoService::SaveReportWithUser(IN nn::account::Uid _0, IN uint64_t _1, IN gpid _2, IN int8_t * _3, guint _3_size, IN uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(5, 0, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::prepo::detail::ipc::IPrepoService::SaveSystemReport(IN nn::ApplicationId _0, IN int8_t * _1, guint _1_size, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(5, 0, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::prepo::detail::ipc::IPrepoService::SaveSystemReportWithUser(IN nn::account::Uid _0, IN nn::ApplicationId _1, IN int8_t * _2, guint _2_size, IN uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(9, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(5, 0, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::prepo::detail::ipc::IPrepoService::SetUserAgreementCheckEnabled(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::psc::sf {
	class IPmControl {
	public:
		IPmControl();
	};
	class IPmModule {
	public:
		IPmModule();
		uint32_t Unknown0(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT KObject * _2);
	};
	class IPmService {
	public:
		IPmService();
		uint32_t GetIPmModule(OUT nn::psc::sf::IPmModule * _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::psc::sf::IPmModule::Unknown0(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	shared_ptr<KObject> temp4;
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	if(temp4 != nullptr)
		resp.copy(0, ctu->newHandle(temp4));
	return ret;
}
uint32_t nn::psc::sf::IPmService::GetIPmModule(OUT nn::psc::sf::IPmModule * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::psc::sf::IPmModule(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::psm {
	class IPsmServer {
	public:
		IPsmServer();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown14();
		uint32_t Unknown15();
		uint32_t Unknown16();
		uint32_t Unknown17();
		uint32_t Unknown18();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
	class IPsmSession {
	public:
		IPsmSession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::psm::IPsmServer::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown14() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown15() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown16() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown17() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown18() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmServer::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmSession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmSession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmSession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmSession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::psm::IPsmSession::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::pwm {
	class IChannelSession {
	public:
		IChannelSession();
		uint32_t Unknown0(IN uint64_t _0);
		uint32_t Unknown1(OUT uint64_t& _0);
		uint32_t Unknown2(IN uint32_t _0);
		uint32_t Unknown3(OUT uint32_t& _0);
		uint32_t Unknown4(IN uint8_t _0);
		uint32_t Unknown5(OUT uint8_t& _0);
	};
	class IManager {
	public:
		IManager();
		uint32_t Unknown0(IN uint32_t _0, OUT IUnknown * _1);
		uint32_t Unknown1(IN uint32_t _0, OUT IUnknown * _1);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::pwm::IChannelSession::Unknown0(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pwm::IChannelSession::Unknown1(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pwm::IChannelSession::Unknown2(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pwm::IChannelSession::Unknown3(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pwm::IChannelSession::Unknown4(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pwm::IChannelSession::Unknown5(OUT uint8_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::pwm::IManager::Unknown0(IN uint32_t _0, OUT IUnknown * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::pwm::IManager::Unknown1(IN uint32_t _0, OUT IUnknown * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::ro::detail {
	class IDebugMonitorInterface {
	public:
		IDebugMonitorInterface();
		uint32_t Unknown0();
	};
	class ILdrShellInterface {
	public:
		ILdrShellInterface();
		uint32_t AddProcessToLaunchQueue(IN uint8_t * _0, guint _0_size, IN uint32_t size, IN nn::ncm::ApplicationId appID);
		uint32_t ClearLaunchQueue();
	};
	class IRoInterface {
	public:
		IRoInterface();
		uint32_t Unknown0(IN uint64_t _0, IN uint64_t _1, IN uint64_t _2, IN uint64_t _3, IN uint64_t _4, IN gpid _5, OUT uint64_t& _6);
		uint32_t Unknown1(IN uint64_t _0, IN uint64_t _1, IN gpid _2);
		uint32_t Unknown2(IN uint64_t _0, IN uint64_t _1, IN uint64_t _2, IN gpid _3);
		uint32_t Unknown3(IN uint64_t _0, IN uint64_t _1, IN gpid _2);
		uint32_t Unknown4(IN uint64_t _0, IN gpid _1, IN KObject * _2);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::ro::detail::IDebugMonitorInterface::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ro::detail::ILdrShellInterface::AddProcessToLaunchQueue(IN uint8_t * _0, guint _0_size, IN uint32_t size, IN nn::ncm::ApplicationId appID) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ro::detail::ILdrShellInterface::ClearLaunchQueue() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ro::detail::IRoInterface::Unknown0(IN uint64_t _0, IN uint64_t _1, IN uint64_t _2, IN uint64_t _3, IN uint64_t _4, IN gpid _5, OUT uint64_t& _6) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ro::detail::IRoInterface::Unknown1(IN uint64_t _0, IN uint64_t _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ro::detail::IRoInterface::Unknown2(IN uint64_t _0, IN uint64_t _1, IN uint64_t _2, IN gpid _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ro::detail::IRoInterface::Unknown3(IN uint64_t _0, IN uint64_t _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ro::detail::IRoInterface::Unknown4(IN uint64_t _0, IN gpid _1, IN KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::sasbus {
	class IManager {
	public:
		IManager();
		uint32_t Unknown0();
	};
	class ISession {
	public:
		ISession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::sasbus::IManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::sasbus::ISession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::sasbus::ISession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::sasbus::ISession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::sasbus::ISession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::settings {
	class IFactorySettingsServer {
	public:
		IFactorySettingsServer();
		uint32_t GetAccelerometerOffset(OUT nn::settings::factory::AccelerometerOffset& _0);
		uint32_t GetAccelerometerScale(OUT nn::settings::factory::AccelerometerScale& _0);
		uint32_t GetBatteryLot(OUT nn::settings::factory::BatteryLot& _0);
		uint32_t GetBluetoothBdAddress(OUT nn::settings::factory::BdAddress& _0);
		uint32_t GetConfigurationId1(OUT nn::settings::factory::ConfigurationId1& _0);
		uint32_t GetEciDeviceCertificate(OUT nn::settings::factory::EccB233DeviceCertificate * _0, guint _0_size);
		uint32_t GetEciDeviceKey(OUT nn::settings::factory::EccB233DeviceKey& _0);
		uint32_t GetEticketDeviceCertificate(OUT nn::settings::factory::Rsa2048DeviceCertificate * _0, guint _0_size);
		uint32_t GetEticketDeviceKey(OUT nn::settings::factory::Rsa2048DeviceKey * _0, guint _0_size);
		uint32_t GetGameCardCertificate(OUT nn::settings::factory::GameCardCertificate * _0, guint _0_size);
		uint32_t GetGameCardKey(OUT nn::settings::factory::GameCardKey * _0, guint _0_size);
		uint32_t GetGyroscopeOffset(OUT nn::settings::factory::GyroscopeOffset& _0);
		uint32_t GetGyroscopeScale(OUT nn::settings::factory::GyroscopeScale& _0);
		uint32_t GetSerialNumber(OUT nn::settings::factory::SerialNumber& _0);
		uint32_t GetSpeakerParameter(OUT nn::settings::factory::SpeakerParameter& _0);
		uint32_t GetSslCertificate(OUT nn::settings::factory::SslCertificate * _0, guint _0_size);
		uint32_t GetSslKey(OUT nn::settings::factory::SslKey * _0, guint _0_size);
		uint32_t GetWirelessLanCountryCodeCount(OUT int32_t& _0);
		uint32_t GetWirelessLanCountryCodes(OUT int32_t& _0, OUT nn::settings::factory::CountryCode * _1, guint _1_size);
		uint32_t GetWirelessLanMacAddress(OUT nn::settings::factory::MacAddress& _0);
		uint32_t SetInitialSystemAppletProgramId(IN nn::ncm::ProgramId _0);
		uint32_t SetOverlayDispProgramId(IN nn::ncm::ProgramId _0);
	};
	class IFirmwareDebugSettingsServer {
	public:
		IFirmwareDebugSettingsServer();
		uint32_t CreateSettingsItemKeyIterator(IN nn::settings::SettingsName * _0, guint _0_size, OUT nn::settings::ISettingsItemKeyIterator * _1);
		uint32_t ResetSettingsItemValue(IN nn::settings::SettingsName * _0, guint _0_size, IN nn::settings::SettingsItemKey * _1, guint _1_size);
		uint32_t SetSettingsItemValue(IN nn::settings::SettingsName * _0, guint _0_size, IN nn::settings::SettingsItemKey * _1, guint _1_size, IN uint8_t * _2, guint _2_size);
	};
	class ISettingsItemKeyIterator {
	public:
		ISettingsItemKeyIterator();
		uint32_t GetKey(OUT uint64_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetKeySize(OUT uint64_t& _0);
		uint32_t GoNext();
	};
	class ISettingsServer {
	public:
		ISettingsServer();
		uint32_t GetAvailableLanguageCodeCount(OUT int32_t& _0);
		uint32_t GetAvailableLanguageCodes(OUT int32_t& _0, OUT nn::settings::LanguageCode * _1, guint _1_size);
		uint32_t GetLanguageCode(OUT nn::settings::LanguageCode& _0);
		uint32_t GetRegionCode(OUT int32_t& _0);
	};
	class ISystemSettingsServer {
	public:
		ISystemSettingsServer();
		uint32_t AcquireFatalDirtyFlagEventHandle(OUT KObject * _0);
		uint32_t AcquireTelemetryDirtyFlagEventHandle(OUT KObject * _0);
		uint32_t GetAccountNotificationSettings(OUT int32_t& _0, OUT nn::settings::system::AccountNotificationSettings * _1, guint _1_size);
		uint32_t GetAccountSettings(OUT nn::settings::system::AccountSettings& _0);
		uint32_t GetAudioOutputMode(IN int32_t _0, OUT int32_t& _1);
		uint32_t GetAudioVolume(IN int32_t _0, OUT nn::settings::system::AudioVolume& _1);
		uint32_t GetAutoUpdateEnableFlag(OUT bool& _0);
		uint32_t GetAutomaticApplicationDownloadFlag(OUT bool& _0);
		uint32_t GetBacklightSettings(OUT nn::settings::system::BacklightSettings& _0);
		uint32_t GetBacklightSettingsEx(OUT nn::settings::system::BacklightSettingsEx& _0);
		uint32_t GetBatteryLot(OUT nn::settings::system::BatteryLot& _0);
		uint32_t GetBatteryPercentageFlag(OUT bool& _0);
		uint32_t GetBluetoothAfhEnableFlag(OUT bool& _0);
		uint32_t GetBluetoothBoostEnableFlag(OUT bool& _0);
		uint32_t GetBluetoothDevicesSettings(OUT int32_t& _0, OUT nn::settings::system::BluetoothDevicesSettings * _1, guint _1_size);
		uint32_t GetBluetoothEnableFlag(OUT bool& _0);
		uint32_t GetColorSetId(OUT int32_t& _0);
		uint32_t GetConsoleInformationUploadFlag(OUT bool& _0);
		uint32_t GetDataDeletionSettings(OUT nn::settings::system::DataDeletionSettings& _0);
		uint32_t GetDebugModeFlag(OUT bool& _0);
		uint32_t GetDeviceNickName(OUT nn::settings::system::DeviceNickName * _0, guint _0_size);
		uint32_t GetDeviceTimeZoneLocationName(OUT nn::time::LocationName& _0);
		uint32_t GetEdid(OUT nn::settings::system::Edid * _0, guint _0_size);
		uint32_t GetEulaVersions(OUT int32_t& _0, OUT nn::settings::system::EulaVersion * _1, guint _1_size);
		uint32_t GetExternalRtcResetFlag(OUT bool& _0);
		uint32_t GetExternalSteadyClockInternalOffset(OUT int64_t& _0);
		uint32_t GetExternalSteadyClockSourceId(OUT nn::util::Uuid& _0);
		uint32_t GetFatalDirtyFlags(OUT nn::settings::system::FatalDirtyFlag& _0);
		uint32_t GetFirmwareVersion(OUT nn::settings::system::FirmwareVersion * _0, guint _0_size);
		uint32_t GetFirmwareVersion2(OUT nn::settings::system::FirmwareVersion * _0, guint _0_size);
		uint32_t GetHeadphoneVolumeUpdateFlag(OUT bool& _0);
		uint32_t GetHeadphoneVolumeWarningCount(OUT int32_t& _0);
		uint32_t GetInRepairProcessEnableFlag(OUT bool& _0);
		uint32_t GetInitialLaunchSettings(OUT nn::settings::system::InitialLaunchSettings& _0);
		uint32_t GetInitialSystemAppletProgramId(OUT nn::ncm::ProgramId& _0);
		uint32_t GetLdnChannel(OUT int32_t& _0);
		uint32_t GetLockScreenFlag(OUT bool& _0);
		uint32_t GetMiiAuthorId(OUT nn::util::Uuid& _0);
		uint32_t GetNetworkSettings(OUT int32_t& _0, OUT nn::settings::system::NetworkSettings * _1, guint _1_size);
		uint32_t GetNetworkSystemClockContext(OUT nn::time::SystemClockContext& _0);
		uint32_t GetNfcEnableFlag(OUT bool& _0);
		uint32_t GetNotificationSettings(OUT nn::settings::system::NotificationSettings& _0);
		uint32_t GetNxControllerSettings(OUT int32_t& _0, OUT nn::settings::system::NxControllerSettings * _1, guint _1_size);
		uint32_t GetOverlayDispProgramId(OUT nn::ncm::ProgramId& _0);
		uint32_t GetPrimaryAlbumStorage(OUT int32_t& _0);
		uint32_t GetProductModel(OUT int32_t& _0);
		uint32_t GetPtmBatteryLot(OUT nn::settings::factory::BatteryLot& _0);
		uint32_t GetPtmFuelGaugeParameter(OUT nn::settings::system::PtmFuelGaugeParameter& _0);
		uint32_t GetPushNotificationActivityModeOnSleep(OUT int32_t& _0);
		uint32_t GetQuestFlag(OUT bool& _0);
		uint32_t GetSerialNumber(OUT nn::settings::system::SerialNumber& _0);
		uint32_t GetSettingsItemValue(IN nn::settings::SettingsName * _0, guint _0_size, IN nn::settings::SettingsItemKey * _1, guint _1_size, OUT uint64_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t GetSettingsItemValueSize(IN nn::settings::SettingsName * _0, guint _0_size, IN nn::settings::SettingsItemKey * _1, guint _1_size, OUT uint64_t& _2);
		uint32_t GetShutdownRtcValue(OUT int64_t& _0);
		uint32_t GetSleepSettings(OUT nn::settings::system::SleepSettings& _0);
		uint32_t GetTelemetryDirtyFlags(OUT nn::settings::system::TelemetryDirtyFlag& _0);
		uint32_t GetTvSettings(OUT nn::settings::system::TvSettings& _0);
		uint32_t GetUsb30EnableFlag(OUT bool& _0);
		uint32_t GetUsbFullKeyEnableFlag(OUT bool& _0);
		uint32_t GetUserSystemClockContext(OUT nn::time::SystemClockContext& _0);
		uint32_t GetVibrationMasterVolume(OUT float32_t& _0);
		uint32_t GetWirelessCertificationFile(OUT uint64_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetWirelessCertificationFileSize(OUT uint64_t& _0);
		uint32_t GetWirelessLanEnableFlag(OUT bool& _0);
		uint32_t IsForceMuteOnHeadphoneRemoved(OUT bool& _0);
		uint32_t IsUserSystemClockAutomaticCorrectionEnabled(OUT bool& _0);
		uint32_t NeedsToUpdateHeadphoneVolume(IN bool _0, OUT bool& _1, OUT bool& _2, OUT int8_t& _3);
		uint32_t SetAccountNotificationSettings(IN nn::settings::system::AccountNotificationSettings * _0, guint _0_size);
		uint32_t SetAccountSettings(IN nn::settings::system::AccountSettings _0);
		uint32_t SetAudioOutputMode(IN int32_t _0, IN int32_t _1);
		uint32_t SetAudioVolume(IN nn::settings::system::AudioVolume _0, IN int32_t _1);
		uint32_t SetAutoUpdateEnableFlag(IN bool _0);
		uint32_t SetAutomaticApplicationDownloadFlag(IN bool _0);
		uint32_t SetBacklightSettings(IN nn::settings::system::BacklightSettings _0);
		uint32_t SetBacklightSettingsEx(IN nn::settings::system::BacklightSettingsEx _0);
		uint32_t SetBatteryPercentageFlag(IN bool _0);
		uint32_t SetBluetoothAfhEnableFlag(IN bool _0);
		uint32_t SetBluetoothBoostEnableFlag(IN bool _0);
		uint32_t SetBluetoothDevicesSettings(IN nn::settings::system::BluetoothDevicesSettings * _0, guint _0_size);
		uint32_t SetBluetoothEnableFlag(IN bool _0);
		uint32_t SetColorSetId(IN int32_t _0);
		uint32_t SetConsoleInformationUploadFlag(IN bool _0);
		uint32_t SetDataDeletionSettings(IN nn::settings::system::DataDeletionSettings _0);
		uint32_t SetDeviceNickName(IN nn::settings::system::DeviceNickName * _0, guint _0_size);
		uint32_t SetDeviceTimeZoneLocationName(IN nn::time::LocationName _0);
		uint32_t SetEdid(IN nn::settings::system::Edid * _0, guint _0_size);
		uint32_t SetEulaVersions(IN nn::settings::system::EulaVersion * _0, guint _0_size);
		uint32_t SetExternalRtcResetFlag(IN bool _0);
		uint32_t SetExternalSteadyClockInternalOffset(IN int64_t _0);
		uint32_t SetExternalSteadyClockSourceId(IN nn::util::Uuid _0);
		uint32_t SetForceMuteOnHeadphoneRemoved(IN bool _0);
		uint32_t SetHeadphoneVolumeUpdateFlag(IN bool _0);
		uint32_t SetHeadphoneVolumeWarningCount(IN int32_t _0);
		uint32_t SetInRepairProcessEnableFlag(IN bool _0);
		uint32_t SetInitialLaunchSettings(IN nn::settings::system::InitialLaunchSettings _0);
		uint32_t SetLanguageCode(IN nn::settings::LanguageCode _0);
		uint32_t SetLdnChannel(IN int32_t _0);
		uint32_t SetLockScreenFlag(IN bool _0);
		uint32_t SetNetworkSettings(IN nn::settings::system::NetworkSettings * _0, guint _0_size);
		uint32_t SetNetworkSystemClockContext(IN nn::time::SystemClockContext _0);
		uint32_t SetNfcEnableFlag(IN bool _0);
		uint32_t SetNotificationSettings(IN nn::settings::system::NotificationSettings _0);
		uint32_t SetNxControllerSettings(IN nn::settings::system::NxControllerSettings * _0, guint _0_size);
		uint32_t SetPrimaryAlbumStorage(IN int32_t _0);
		uint32_t SetPtmBatteryLot(IN nn::settings::factory::BatteryLot _0);
		uint32_t SetPtmFuelGaugeParameter(IN nn::settings::system::PtmFuelGaugeParameter _0);
		uint32_t SetPushNotificationActivityModeOnSleep(IN int32_t _0);
		uint32_t SetQuestFlag(IN bool _0);
		uint32_t SetRegionCode(IN int32_t _0);
		uint32_t SetShutdownRtcValue(IN int64_t _0);
		uint32_t SetSleepSettings(IN nn::settings::system::SleepSettings _0);
		uint32_t SetTvSettings(IN nn::settings::system::TvSettings _0);
		uint32_t SetUsb30EnableFlag(IN bool _0);
		uint32_t SetUsbFullKeyEnableFlag(IN bool _0);
		uint32_t SetUserSystemClockAutomaticCorrectionEnabled(IN bool _0);
		uint32_t SetUserSystemClockContext(IN nn::time::SystemClockContext _0);
		uint32_t SetVibrationMasterVolume(IN float32_t _0);
		uint32_t SetWirelessLanEnableFlag(IN bool _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::settings::IFactorySettingsServer::GetAccelerometerOffset(OUT nn::settings::factory::AccelerometerOffset& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::AccelerometerOffset>(0xc);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetAccelerometerScale(OUT nn::settings::factory::AccelerometerScale& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::AccelerometerScale>(0xc);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetBatteryLot(OUT nn::settings::factory::BatteryLot& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::BatteryLot>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetBluetoothBdAddress(OUT nn::settings::factory::BdAddress& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::BdAddress>(0xc);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetConfigurationId1(OUT nn::settings::factory::ConfigurationId1& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::ConfigurationId1>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetEciDeviceCertificate(OUT nn::settings::factory::EccB233DeviceCertificate * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetEciDeviceKey(OUT nn::settings::factory::EccB233DeviceKey& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::EccB233DeviceKey>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetEticketDeviceCertificate(OUT nn::settings::factory::Rsa2048DeviceCertificate * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetEticketDeviceKey(OUT nn::settings::factory::Rsa2048DeviceKey * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetGameCardCertificate(OUT nn::settings::factory::GameCardCertificate * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetGameCardKey(OUT nn::settings::factory::GameCardKey * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetGyroscopeOffset(OUT nn::settings::factory::GyroscopeOffset& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::GyroscopeOffset>(0xc);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetGyroscopeScale(OUT nn::settings::factory::GyroscopeScale& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::GyroscopeScale>(0xc);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetSerialNumber(OUT nn::settings::factory::SerialNumber& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::SerialNumber>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetSpeakerParameter(OUT nn::settings::factory::SpeakerParameter& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::SpeakerParameter>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetSslCertificate(OUT nn::settings::factory::SslCertificate * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetSslKey(OUT nn::settings::factory::SslKey * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetWirelessLanCountryCodeCount(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetWirelessLanCountryCodes(OUT int32_t& _0, OUT nn::settings::factory::CountryCode * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::GetWirelessLanMacAddress(OUT nn::settings::factory::MacAddress& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::MacAddress>(0xc);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::SetInitialSystemAppletProgramId(IN nn::ncm::ProgramId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFactorySettingsServer::SetOverlayDispProgramId(IN nn::ncm::ProgramId _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::IFirmwareDebugSettingsServer::CreateSettingsItemKeyIterator(IN nn::settings::SettingsName * _0, guint _0_size, OUT nn::settings::ISettingsItemKeyIterator * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	_1 OMG = new nn::settings::ISettingsItemKeyIterator(resp.move_handles[0]);
	return ret;
}
uint32_t nn::settings::IFirmwareDebugSettingsServer::ResetSettingsItemValue(IN nn::settings::SettingsName * _0, guint _0_size, IN nn::settings::SettingsItemKey * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::settings::IFirmwareDebugSettingsServer::SetSettingsItemValue(IN nn::settings::SettingsName * _0, guint _0_size, IN nn::settings::SettingsItemKey * _1, guint _1_size, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(5, 0, temp8);
	ctu->cpu.readmem(temp7, temp9, temp8);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	delete[] temp9;
	return ret;
}
uint32_t nn::settings::ISettingsItemKeyIterator::GetKey(OUT uint64_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISettingsItemKeyIterator::GetKeySize(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISettingsItemKeyIterator::GoNext() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISettingsServer::GetAvailableLanguageCodeCount(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISettingsServer::GetAvailableLanguageCodes(OUT int32_t& _0, OUT nn::settings::LanguageCode * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISettingsServer::GetLanguageCode(OUT nn::settings::LanguageCode& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISettingsServer::GetRegionCode(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::AcquireFatalDirtyFlagEventHandle(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::AcquireTelemetryDirtyFlagEventHandle(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetAccountNotificationSettings(OUT int32_t& _0, OUT nn::settings::system::AccountNotificationSettings * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetAccountSettings(OUT nn::settings::system::AccountSettings& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetAudioOutputMode(IN int32_t _0, OUT int32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetAudioVolume(IN int32_t _0, OUT nn::settings::system::AudioVolume& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetAutoUpdateEnableFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetAutomaticApplicationDownloadFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetBacklightSettings(OUT nn::settings::system::BacklightSettings& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::system::BacklightSettings>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetBacklightSettingsEx(OUT nn::settings::system::BacklightSettingsEx& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::system::BacklightSettingsEx>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetBatteryLot(OUT nn::settings::system::BatteryLot& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::system::BatteryLot>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetBatteryPercentageFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetBluetoothAfhEnableFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetBluetoothBoostEnableFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetBluetoothDevicesSettings(OUT int32_t& _0, OUT nn::settings::system::BluetoothDevicesSettings * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetBluetoothEnableFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetColorSetId(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetConsoleInformationUploadFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetDataDeletionSettings(OUT nn::settings::system::DataDeletionSettings& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetDebugModeFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetDeviceNickName(OUT nn::settings::system::DeviceNickName * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetDeviceTimeZoneLocationName(OUT nn::time::LocationName& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::time::LocationName>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetEdid(OUT nn::settings::system::Edid * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetEulaVersions(OUT int32_t& _0, OUT nn::settings::system::EulaVersion * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetExternalRtcResetFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetExternalSteadyClockInternalOffset(OUT int64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetExternalSteadyClockSourceId(OUT nn::util::Uuid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetFatalDirtyFlags(OUT nn::settings::system::FatalDirtyFlag& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetFirmwareVersion(OUT nn::settings::system::FirmwareVersion * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetFirmwareVersion2(OUT nn::settings::system::FirmwareVersion * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x1a, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetHeadphoneVolumeUpdateFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetHeadphoneVolumeWarningCount(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetInRepairProcessEnableFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetInitialLaunchSettings(OUT nn::settings::system::InitialLaunchSettings& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::system::InitialLaunchSettings>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetInitialSystemAppletProgramId(OUT nn::ncm::ProgramId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetLdnChannel(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetLockScreenFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetMiiAuthorId(OUT nn::util::Uuid& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetNetworkSettings(OUT int32_t& _0, OUT nn::settings::system::NetworkSettings * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetNetworkSystemClockContext(OUT nn::time::SystemClockContext& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::time::SystemClockContext>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetNfcEnableFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetNotificationSettings(OUT nn::settings::system::NotificationSettings& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::system::NotificationSettings>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetNxControllerSettings(OUT int32_t& _0, OUT nn::settings::system::NxControllerSettings * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetOverlayDispProgramId(OUT nn::ncm::ProgramId& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetPrimaryAlbumStorage(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetProductModel(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetPtmBatteryLot(OUT nn::settings::factory::BatteryLot& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::factory::BatteryLot>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetPtmFuelGaugeParameter(OUT nn::settings::system::PtmFuelGaugeParameter& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::system::PtmFuelGaugeParameter>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetPushNotificationActivityModeOnSleep(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetQuestFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetSerialNumber(OUT nn::settings::system::SerialNumber& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::system::SerialNumber>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetSettingsItemValue(IN nn::settings::SettingsName * _0, guint _0_size, IN nn::settings::SettingsItemKey * _1, guint _1_size, OUT uint64_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(6, 0, temp8);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	ctu->cpu.writemem(temp7, temp9, temp8);
	delete[] temp9;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetSettingsItemValueSize(IN nn::settings::SettingsName * _0, guint _0_size, IN nn::settings::SettingsItemKey * _1, guint _1_size, OUT uint64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x19, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetShutdownRtcValue(OUT int64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetSleepSettings(OUT nn::settings::system::SleepSettings& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::system::SleepSettings>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetTelemetryDirtyFlags(OUT nn::settings::system::TelemetryDirtyFlag& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetTvSettings(OUT nn::settings::system::TvSettings& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::settings::system::TvSettings>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetUsb30EnableFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetUsbFullKeyEnableFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetUserSystemClockContext(OUT nn::time::SystemClockContext& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::time::SystemClockContext>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetVibrationMasterVolume(OUT float32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetWirelessCertificationFile(OUT uint64_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetWirelessCertificationFileSize(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::GetWirelessLanEnableFlag(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::IsForceMuteOnHeadphoneRemoved(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::IsUserSystemClockAutomaticCorrectionEnabled(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::NeedsToUpdateHeadphoneVolume(IN bool _0, OUT bool& _1, OUT bool& _2, OUT int8_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetAccountNotificationSettings(IN nn::settings::system::AccountNotificationSettings * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetAccountSettings(IN nn::settings::system::AccountSettings _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetAudioOutputMode(IN int32_t _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetAudioVolume(IN nn::settings::system::AudioVolume _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetAutoUpdateEnableFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetAutomaticApplicationDownloadFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetBacklightSettings(IN nn::settings::system::BacklightSettings _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetBacklightSettingsEx(IN nn::settings::system::BacklightSettingsEx _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetBatteryPercentageFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetBluetoothAfhEnableFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetBluetoothBoostEnableFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetBluetoothDevicesSettings(IN nn::settings::system::BluetoothDevicesSettings * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetBluetoothEnableFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetColorSetId(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetConsoleInformationUploadFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetDataDeletionSettings(IN nn::settings::system::DataDeletionSettings _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetDeviceNickName(IN nn::settings::system::DeviceNickName * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x15, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetDeviceTimeZoneLocationName(IN nn::time::LocationName _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetEdid(IN nn::settings::system::Edid * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x19, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetEulaVersions(IN nn::settings::system::EulaVersion * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetExternalRtcResetFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetExternalSteadyClockInternalOffset(IN int64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetExternalSteadyClockSourceId(IN nn::util::Uuid _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetForceMuteOnHeadphoneRemoved(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetHeadphoneVolumeUpdateFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetHeadphoneVolumeWarningCount(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetInRepairProcessEnableFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetInitialLaunchSettings(IN nn::settings::system::InitialLaunchSettings _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetLanguageCode(IN nn::settings::LanguageCode _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetLdnChannel(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetLockScreenFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetNetworkSettings(IN nn::settings::system::NetworkSettings * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetNetworkSystemClockContext(IN nn::time::SystemClockContext _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetNfcEnableFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetNotificationSettings(IN nn::settings::system::NotificationSettings _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetNxControllerSettings(IN nn::settings::system::NxControllerSettings * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetPrimaryAlbumStorage(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetPtmBatteryLot(IN nn::settings::factory::BatteryLot _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetPtmFuelGaugeParameter(IN nn::settings::system::PtmFuelGaugeParameter _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetPushNotificationActivityModeOnSleep(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetQuestFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetRegionCode(IN int32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetShutdownRtcValue(IN int64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetSleepSettings(IN nn::settings::system::SleepSettings _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetTvSettings(IN nn::settings::system::TvSettings _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetUsb30EnableFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetUsbFullKeyEnableFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetUserSystemClockAutomaticCorrectionEnabled(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetUserSystemClockContext(IN nn::time::SystemClockContext _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetVibrationMasterVolume(IN float32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::settings::ISystemSettingsServer::SetWirelessLanEnableFlag(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::sm::detail {
	class IManagerInterface {
	public:
		IManagerInterface();
		uint32_t Unknown0(IN uint64_t _0, IN uint8_t * _1, guint _1_size, IN uint8_t * _2, guint _2_size);
		uint32_t Unknown1(IN uint64_t _0);
	};
	class IUserInterface {
	public:
		IUserInterface();
		uint32_t Unknown0(IN uint64_t _0, IN gpid _1);
		uint32_t Unknown1(IN uint64_t _0, OUT KObject * _1);
		uint32_t Unknown2(IN uint64_t _0, IN uint8_t _1, IN uint32_t _2, OUT KObject * _3);
		uint32_t Unknown3(IN uint64_t _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::sm::detail::IManagerInterface::Unknown0(IN uint64_t _0, IN uint8_t * _1, guint _1_size, IN uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(5, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::sm::detail::IManagerInterface::Unknown1(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::sm::detail::IUserInterface::Unknown0(IN uint64_t _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::sm::detail::IUserInterface::Unknown1(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::sm::detail::IUserInterface::Unknown2(IN uint64_t _0, IN uint8_t _1, IN uint32_t _2, OUT KObject * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::sm::detail::IUserInterface::Unknown3(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::socket::resolver {
	class IResolver {
	public:
		IResolver();
		uint32_t Unknown0(IN uint32_t _0, IN uint8_t * _1, guint _1_size);
		uint32_t Unknown1(IN uint32_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown2(IN uint8_t _0, IN uint32_t _1, IN uint64_t _2, IN gpid _3, IN uint8_t * _4, guint _4_size, OUT uint32_t& _5, OUT uint32_t& _6, OUT uint32_t& _7, OUT uint8_t * _8, guint _8_size);
		uint32_t Unknown3(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint64_t _3, IN gpid _4, IN uint8_t * _5, guint _5_size, OUT uint32_t& _6, OUT uint32_t& _7, OUT uint32_t& _8, OUT uint8_t * _9, guint _9_size);
		uint32_t Unknown4(IN uint32_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown5(IN uint32_t _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Unknown6(IN uint8_t _0, IN uint32_t _1, IN uint64_t _2, IN gpid _3, IN uint8_t * _4, guint _4_size, IN uint8_t * _5, guint _5_size, IN uint8_t * _6, guint _6_size, OUT uint32_t& _7, OUT uint32_t& _8, OUT uint32_t& _9, OUT uint8_t * _10, guint _10_size);
		uint32_t Unknown7(IN uint32_t _0, IN uint32_t _1, IN uint64_t _2, IN gpid _3, IN uint8_t * _4, guint _4_size, OUT uint32_t& _5, OUT uint32_t& _6, OUT uint8_t * _7, guint _7_size, OUT uint8_t * _8, guint _8_size);
		uint32_t Unknown8(IN uint64_t _0, IN gpid _1, OUT uint32_t& _2);
		uint32_t Unknown9(IN uint32_t _0, IN uint64_t _1, IN gpid _2);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::socket::resolver::IResolver::Unknown0(IN uint32_t _0, IN uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::resolver::IResolver::Unknown1(IN uint32_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::resolver::IResolver::Unknown2(IN uint8_t _0, IN uint32_t _1, IN uint64_t _2, IN gpid _3, IN uint8_t * _4, guint _4_size, OUT uint32_t& _5, OUT uint32_t& _6, OUT uint32_t& _7, OUT uint8_t * _8, guint _8_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::socket::resolver::IResolver::Unknown3(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint64_t _3, IN gpid _4, IN uint8_t * _5, guint _5_size, OUT uint32_t& _6, OUT uint32_t& _7, OUT uint32_t& _8, OUT uint8_t * _9, guint _9_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::socket::resolver::IResolver::Unknown4(IN uint32_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::resolver::IResolver::Unknown5(IN uint32_t _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::resolver::IResolver::Unknown6(IN uint8_t _0, IN uint32_t _1, IN uint64_t _2, IN gpid _3, IN uint8_t * _4, guint _4_size, IN uint8_t * _5, guint _5_size, IN uint8_t * _6, guint _6_size, OUT uint32_t& _7, OUT uint32_t& _8, OUT uint32_t& _9, OUT uint8_t * _10, guint _10_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(5, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(5, 2, temp8);
	ctu->cpu.readmem(temp7, temp9, temp8);
	guint temp11;
	auto temp10 = req.getBuffer(6, 0, temp11);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	delete[] temp9;
	ctu->cpu.writemem(temp10, temp12, temp11);
	delete[] temp12;
	return ret;
}
uint32_t nn::socket::resolver::IResolver::Unknown7(IN uint32_t _0, IN uint32_t _1, IN uint64_t _2, IN gpid _3, IN uint8_t * _4, guint _4_size, OUT uint32_t& _5, OUT uint32_t& _6, OUT uint8_t * _7, guint _7_size, OUT uint8_t * _8, guint _8_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(6, 1, temp8);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	ctu->cpu.writemem(temp7, temp9, temp8);
	delete[] temp9;
	return ret;
}
uint32_t nn::socket::resolver::IResolver::Unknown8(IN uint64_t _0, IN gpid _1, OUT uint32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::socket::resolver::IResolver::Unknown9(IN uint32_t _0, IN uint64_t _1, IN gpid _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::socket::sf {
	class IClient {
	public:
		IClient();
		uint32_t Unknown0(IN uint8_t * _0, IN uint64_t _1, IN uint64_t _2, IN gpid _3, IN KObject * _4, OUT uint32_t& _5);
		uint32_t Unknown1(IN uint64_t _0, IN gpid _1);
		uint32_t Unknown10(IN uint32_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size, OUT uint32_t& _3, OUT uint32_t& _4);
		uint32_t Unknown11(IN uint32_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size, IN uint8_t * _3, guint _3_size, OUT uint32_t& _4, OUT uint32_t& _5);
		uint32_t Unknown12(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t Unknown13(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown14(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown15(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t Unknown16(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t Unknown17(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, OUT uint32_t& _3, OUT uint32_t& _4, OUT uint32_t& _5, OUT uint8_t * _6, guint _6_size);
		uint32_t Unknown18(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown19(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, IN uint8_t * _4, guint _4_size, IN uint8_t * _5, guint _5_size, IN uint8_t * _6, guint _6_size, OUT uint32_t& _7, OUT uint32_t& _8, OUT uint8_t * _9, guint _9_size, OUT uint8_t * _10, guint _10_size, OUT uint8_t * _11, guint _11_size, OUT uint8_t * _12, guint _12_size);
		uint32_t Unknown2(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, OUT uint32_t& _3, OUT uint32_t& _4);
		uint32_t Unknown20(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, OUT uint32_t& _3, OUT uint32_t& _4);
		uint32_t Unknown21(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, OUT uint32_t& _4, OUT uint32_t& _5);
		uint32_t Unknown22(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown23(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2);
		uint32_t Unknown24(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown25(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t Unknown26(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2);
		uint32_t Unknown27(IN uint32_t _0, IN uint64_t _1, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown28(IN uint64_t _0, IN gpid _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t Unknown29(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint128_t _3, OUT uint32_t& _4, OUT uint32_t& _5, OUT uint8_t * _6, guint _6_size);
		uint32_t Unknown3(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, OUT uint32_t& _3, OUT uint32_t& _4);
		uint32_t Unknown30(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, IN uint8_t * _4, guint _4_size, OUT uint32_t& _5, OUT uint32_t& _6);
		uint32_t Unknown4(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown5(IN uint32_t _0, IN uint8_t * _1, IN uint8_t * _2, guint _2_size, IN uint8_t * _3, guint _3_size, IN uint8_t * _4, guint _4_size, OUT uint32_t& _5, OUT uint32_t& _6, OUT uint8_t * _7, guint _7_size, OUT uint8_t * _8, guint _8_size, OUT uint8_t * _9, guint _9_size);
		uint32_t Unknown6(IN uint32_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size, OUT uint32_t& _3, OUT uint32_t& _4, OUT uint8_t * _5, guint _5_size);
		uint32_t Unknown7(IN uint8_t * _0, guint _0_size, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint32_t& _4, OUT uint8_t * _5, guint _5_size);
		uint32_t Unknown8(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t Unknown9(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint32_t& _4, OUT uint8_t * _5, guint _5_size, OUT uint8_t * _6, guint _6_size);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::socket::sf::IClient::Unknown0(IN uint8_t * _0, IN uint64_t _1, IN uint64_t _2, IN gpid _3, IN KObject * _4, OUT uint32_t& _5) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown1(IN uint64_t _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown10(IN uint32_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size, OUT uint32_t& _3, OUT uint32_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown11(IN uint32_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size, IN uint8_t * _3, guint _3_size, OUT uint32_t& _4, OUT uint32_t& _5) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x21, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown12(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown13(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown14(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown15(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown16(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown17(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, OUT uint32_t& _3, OUT uint32_t& _4, OUT uint32_t& _5, OUT uint8_t * _6, guint _6_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown18(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown19(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, IN uint8_t * _4, guint _4_size, IN uint8_t * _5, guint _5_size, IN uint8_t * _6, guint _6_size, OUT uint32_t& _7, OUT uint32_t& _8, OUT uint8_t * _9, guint _9_size, OUT uint8_t * _10, guint _10_size, OUT uint8_t * _11, guint _11_size, OUT uint8_t * _12, guint _12_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x21, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(0x21, 2, temp8);
	ctu->cpu.readmem(temp7, temp9, temp8);
	guint temp11;
	auto temp10 = req.getBuffer(0x21, 3, temp11);
	ctu->cpu.readmem(temp10, temp12, temp11);
	guint temp14;
	auto temp13 = req.getBuffer(0x22, 0, temp14);
	guint temp17;
	auto temp16 = req.getBuffer(0x22, 1, temp17);
	guint temp20;
	auto temp19 = req.getBuffer(0x22, 2, temp20);
	guint temp23;
	auto temp22 = req.getBuffer(0x22, 3, temp23);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	delete[] temp9;
	delete[] temp12;
	ctu->cpu.writemem(temp13, temp15, temp14);
	delete[] temp15;
	ctu->cpu.writemem(temp16, temp18, temp17);
	delete[] temp18;
	ctu->cpu.writemem(temp19, temp21, temp20);
	delete[] temp21;
	ctu->cpu.writemem(temp22, temp24, temp23);
	delete[] temp24;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown2(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, OUT uint32_t& _3, OUT uint32_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown20(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, OUT uint32_t& _3, OUT uint32_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown21(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, OUT uint32_t& _4, OUT uint32_t& _5) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown22(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown23(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown24(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown25(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown26(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown27(IN uint32_t _0, IN uint64_t _1, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown28(IN uint64_t _0, IN gpid _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown29(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint128_t _3, OUT uint32_t& _4, OUT uint32_t& _5, OUT uint8_t * _6, guint _6_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown3(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, OUT uint32_t& _3, OUT uint32_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown30(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, IN uint8_t * _4, guint _4_size, OUT uint32_t& _5, OUT uint32_t& _6) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x21, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown4(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown5(IN uint32_t _0, IN uint8_t * _1, IN uint8_t * _2, guint _2_size, IN uint8_t * _3, guint _3_size, IN uint8_t * _4, guint _4_size, OUT uint32_t& _5, OUT uint32_t& _6, OUT uint8_t * _7, guint _7_size, OUT uint8_t * _8, guint _8_size, OUT uint8_t * _9, guint _9_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x21, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(0x21, 2, temp8);
	ctu->cpu.readmem(temp7, temp9, temp8);
	guint temp11;
	auto temp10 = req.getBuffer(0x22, 0, temp11);
	guint temp14;
	auto temp13 = req.getBuffer(0x22, 1, temp14);
	guint temp17;
	auto temp16 = req.getBuffer(0x22, 2, temp17);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	delete[] temp9;
	ctu->cpu.writemem(temp10, temp12, temp11);
	delete[] temp12;
	ctu->cpu.writemem(temp13, temp15, temp14);
	delete[] temp15;
	ctu->cpu.writemem(temp16, temp18, temp17);
	delete[] temp18;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown6(IN uint32_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size, OUT uint32_t& _3, OUT uint32_t& _4, OUT uint8_t * _5, guint _5_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x22, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown7(IN uint8_t * _0, guint _0_size, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint32_t& _4, OUT uint8_t * _5, guint _5_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x21, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	guint temp8;
	auto temp7 = req.getBuffer(0x22, 0, temp8);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	ctu->cpu.writemem(temp7, temp9, temp8);
	delete[] temp9;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown8(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::socket::sf::IClient::Unknown9(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3, OUT uint32_t& _4, OUT uint8_t * _5, guint _5_size, OUT uint8_t * _6, guint _6_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x22, 1, temp5);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::spl::detail {
	class IRandomInterface {
	public:
		IRandomInterface();
		uint32_t Unknown0(OUT uint8_t * _0, guint _0_size);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::spl::detail::IRandomInterface::Unknown0(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::spsm::detail {
	class IPowerStateInterface {
	public:
		IPowerStateInterface();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::spsm::detail::IPowerStateInterface::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::ssl::sf {
	class ISslConnection {
	public:
		ISslConnection();
		uint32_t DoHandshake();
		uint32_t DoHandshakeGetServerCert(OUT uint32_t& _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t FlushSessionCache();
		uint32_t GetHostName(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t GetIoMode(OUT nn::ssl::sf::IoMode& _0);
		uint32_t GetNeededServerCertBufferSize(OUT uint32_t& _0);
		uint32_t GetOption(IN nn::ssl::sf::OptionType _0, OUT bool& _1);
		uint32_t GetRenegotiationMode(OUT nn::ssl::sf::RenegotiationMode& _0);
		uint32_t GetSessionCacheMode(OUT nn::ssl::sf::SessionCacheMode& _0);
		uint32_t GetSocketDescriptor(OUT int32_t& _0);
		uint32_t GetVerifyCertError();
		uint32_t GetVerifyCertErrors(OUT uint32_t& _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t GetVerifyOption(OUT nn::ssl::sf::VerifyOption& _0);
		uint32_t Peek(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t Pending(OUT int32_t& _0);
		uint32_t Poll(IN nn::ssl::sf::PollEvent _0, IN uint32_t _1, OUT nn::ssl::sf::PollEvent& _2);
		uint32_t Read(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size);
		uint32_t SetHostName(IN uint8_t * _0, guint _0_size);
		uint32_t SetIoMode(IN nn::ssl::sf::IoMode _0);
		uint32_t SetOption(IN bool _0, IN nn::ssl::sf::OptionType _1);
		uint32_t SetRenegotiationMode(IN nn::ssl::sf::RenegotiationMode _0);
		uint32_t SetSessionCacheMode(IN nn::ssl::sf::SessionCacheMode _0);
		uint32_t SetSocketDescriptor(IN int32_t _0, OUT int32_t& _1);
		uint32_t SetVerifyOption(IN nn::ssl::sf::VerifyOption _0);
		uint32_t Write(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1);
	};
	class ISslContext {
	public:
		ISslContext();
		uint32_t AddPolicyOid(IN uint8_t * _0, guint _0_size);
		uint32_t CreateConnection(OUT nn::ssl::sf::ISslConnection * _0);
		uint32_t GetConnectionCount(OUT uint32_t& _0);
		uint32_t GetOption(IN nn::ssl::sf::ContextOption _0, OUT int32_t& _1);
		uint32_t ImportClientPki(IN uint8_t * _0, guint _0_size, IN uint8_t * _1, guint _1_size, OUT uint64_t& _2);
		uint32_t ImportCrl(IN uint8_t * _0, guint _0_size, OUT uint64_t& _1);
		uint32_t ImportServerPki(IN nn::ssl::sf::CertificateFormat _0, IN uint8_t * _1, guint _1_size, OUT uint64_t& _2);
		uint32_t RegisterInternalPki(IN nn::ssl::sf::InternalPki _0, OUT uint64_t& _1);
		uint32_t RemoveClientPki(IN uint64_t _0);
		uint32_t RemoveCrl(IN uint64_t _0);
		uint32_t RemoveServerPki(IN uint64_t _0);
		uint32_t SetOption(IN nn::ssl::sf::ContextOption _0, IN int32_t _1);
	};
	class ISslService {
	public:
		ISslService();
		uint32_t CreateContext(IN nn::ssl::sf::SslVersion _0, IN uint64_t _1, IN gpid _2, OUT nn::ssl::sf::ISslContext * _3);
		uint32_t DebugIoctl(IN uint64_t _0, IN uint8_t * _1, guint _1_size, OUT uint8_t * _2, guint _2_size);
		uint32_t GetCertificateBufSize(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1);
		uint32_t GetCertificates(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t GetContextCount(OUT uint32_t& _0);
		uint32_t SetInterfaceVersion(IN uint32_t _0);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::ssl::sf::ISslConnection::DoHandshake() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::DoHandshakeGetServerCert(OUT uint32_t& _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::FlushSessionCache() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::GetHostName(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::GetIoMode(OUT nn::ssl::sf::IoMode& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::GetNeededServerCertBufferSize(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::GetOption(IN nn::ssl::sf::OptionType _0, OUT bool& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::GetRenegotiationMode(OUT nn::ssl::sf::RenegotiationMode& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::GetSessionCacheMode(OUT nn::ssl::sf::SessionCacheMode& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::GetSocketDescriptor(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::GetVerifyCertError() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::GetVerifyCertErrors(OUT uint32_t& _0, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::GetVerifyOption(OUT nn::ssl::sf::VerifyOption& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::Peek(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::Pending(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::Poll(IN nn::ssl::sf::PollEvent _0, IN uint32_t _1, OUT nn::ssl::sf::PollEvent& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::Read(OUT uint32_t& _0, OUT uint8_t * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::SetHostName(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::SetIoMode(IN nn::ssl::sf::IoMode _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::SetOption(IN bool _0, IN nn::ssl::sf::OptionType _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::SetRenegotiationMode(IN nn::ssl::sf::RenegotiationMode _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::SetSessionCacheMode(IN nn::ssl::sf::SessionCacheMode _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::SetSocketDescriptor(IN int32_t _0, OUT int32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::SetVerifyOption(IN nn::ssl::sf::VerifyOption _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslConnection::Write(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::AddPolicyOid(IN uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::CreateConnection(OUT nn::ssl::sf::ISslConnection * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::ssl::sf::ISslConnection(resp.move_handles[0]);
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::GetConnectionCount(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::GetOption(IN nn::ssl::sf::ContextOption _0, OUT int32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::ImportClientPki(IN uint8_t * _0, guint _0_size, IN uint8_t * _1, guint _1_size, OUT uint64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(5, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::ImportCrl(IN uint8_t * _0, guint _0_size, OUT uint64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::ImportServerPki(IN nn::ssl::sf::CertificateFormat _0, IN uint8_t * _1, guint _1_size, OUT uint64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::RegisterInternalPki(IN nn::ssl::sf::InternalPki _0, OUT uint64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::RemoveClientPki(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::RemoveCrl(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::RemoveServerPki(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslContext::SetOption(IN nn::ssl::sf::ContextOption _0, IN int32_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslService::CreateContext(IN nn::ssl::sf::SslVersion _0, IN uint64_t _1, IN gpid _2, OUT nn::ssl::sf::ISslContext * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_3 OMG = new nn::ssl::sf::ISslContext(resp.move_handles[0]);
	return ret;
}
uint32_t nn::ssl::sf::ISslService::DebugIoctl(IN uint64_t _0, IN uint8_t * _1, guint _1_size, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::ssl::sf::ISslService::GetCertificateBufSize(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::ssl::sf::ISslService::GetCertificates(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::ssl::sf::ISslService::GetContextCount(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ssl::sf::ISslService::SetInterfaceVersion(IN uint32_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::tc {
	class IManager {
	public:
		IManager();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::tc::IManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tc::IManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tc::IManager::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tc::IManager::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tc::IManager::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tc::IManager::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tc::IManager::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tc::IManager::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tc::IManager::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::timesrv::detail::service {
	class IStaticService {
	public:
		IStaticService();
		uint32_t GetStandardLocalSystemClock(OUT nn::timesrv::detail::service::ISystemClock * _0);
		uint32_t GetStandardNetworkSystemClock(OUT nn::timesrv::detail::service::ISystemClock * _0);
		uint32_t GetStandardSteadyClock(OUT nn::timesrv::detail::service::ISteadyClock * _0);
		uint32_t GetStandardUserSystemClock(OUT nn::timesrv::detail::service::ISystemClock * _0);
		uint32_t GetTimeZoneService(OUT nn::timesrv::detail::service::ITimeZoneService * _0);
		uint32_t IsStandardNetworkSystemClockAccuracySufficient(OUT bool& _0);
		uint32_t IsStandardUserSystemClockAutomaticCorrectionEnabled(OUT bool& _0);
		uint32_t SetStandardUserSystemClockAutomaticCorrectionEnabled(IN bool _0);
	};
	class ISteadyClock {
	public:
		ISteadyClock();
		uint32_t GetCurrentTimePoint(OUT nn::time::SteadyClockTimePoint& _0);
		uint32_t GetInternalOffset(OUT nn::TimeSpanType& _0);
		uint32_t GetRtcValue(OUT int64_t& _0);
		uint32_t GetSetupResutltValue(OUT uint32_t& _0);
		uint32_t GetTestOffset(OUT nn::TimeSpanType& _0);
		uint32_t IsRtcResetDetected(OUT bool& _0);
		uint32_t SetInternalOffset(IN nn::TimeSpanType _0);
		uint32_t SetTestOffset(IN nn::TimeSpanType _0);
	};
	class ISystemClock {
	public:
		ISystemClock();
		uint32_t GetCurrentTime(OUT nn::time::PosixTime& _0);
		uint32_t GetSystemClockContext(OUT nn::time::SystemClockContext& _0);
		uint32_t SetCurrentTime(IN nn::time::PosixTime _0);
		uint32_t SetSystemClockContext(IN nn::time::SystemClockContext _0);
	};
	class ITimeZoneService {
	public:
		ITimeZoneService();
		uint32_t GetDeviceLocationName(OUT nn::time::LocationName& _0);
		uint32_t GetTimeZoneRuleVersion(OUT nn::time::TimeZoneRuleVersion& _0);
		uint32_t GetTotalLocationNameCount(OUT int32_t& _0);
		uint32_t LoadLocationNameList(IN int32_t _0, OUT int32_t& _1, OUT nn::time::LocationName * _2, guint _2_size);
		uint32_t LoadTimeZoneRule(IN nn::time::LocationName _0, OUT nn::time::TimeZoneRule * _1, guint _1_size);
		uint32_t SetDeviceLocationName(IN nn::time::LocationName _0);
		uint32_t ToCalendarTime(IN nn::time::PosixTime _0, IN nn::time::TimeZoneRule * _1, guint _1_size, OUT nn::time::CalendarTime& _2, OUT nn::time::sf::CalendarAdditionalInfo& _3);
		uint32_t ToCalendarTimeWithMyRule(IN nn::time::PosixTime _0, OUT nn::time::CalendarTime& _1, OUT nn::time::sf::CalendarAdditionalInfo& _2);
		uint32_t ToPosixTime(IN nn::time::CalendarTime _0, IN nn::time::TimeZoneRule * _1, guint _1_size, OUT int32_t& _2, OUT nn::time::PosixTime * _3, guint _3_size);
		uint32_t ToPosixTimeWithMyRule(IN nn::time::CalendarTime _0, OUT int32_t& _1, OUT nn::time::PosixTime * _2, guint _2_size);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::timesrv::detail::service::IStaticService::GetStandardLocalSystemClock(OUT nn::timesrv::detail::service::ISystemClock * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::timesrv::detail::service::ISystemClock(resp.move_handles[0]);
	return ret;
}
uint32_t nn::timesrv::detail::service::IStaticService::GetStandardNetworkSystemClock(OUT nn::timesrv::detail::service::ISystemClock * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::timesrv::detail::service::ISystemClock(resp.move_handles[0]);
	return ret;
}
uint32_t nn::timesrv::detail::service::IStaticService::GetStandardSteadyClock(OUT nn::timesrv::detail::service::ISteadyClock * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::timesrv::detail::service::ISteadyClock(resp.move_handles[0]);
	return ret;
}
uint32_t nn::timesrv::detail::service::IStaticService::GetStandardUserSystemClock(OUT nn::timesrv::detail::service::ISystemClock * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::timesrv::detail::service::ISystemClock(resp.move_handles[0]);
	return ret;
}
uint32_t nn::timesrv::detail::service::IStaticService::GetTimeZoneService(OUT nn::timesrv::detail::service::ITimeZoneService * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::timesrv::detail::service::ITimeZoneService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::timesrv::detail::service::IStaticService::IsStandardNetworkSystemClockAccuracySufficient(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::IStaticService::IsStandardUserSystemClockAutomaticCorrectionEnabled(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::IStaticService::SetStandardUserSystemClockAutomaticCorrectionEnabled(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISteadyClock::GetCurrentTimePoint(OUT nn::time::SteadyClockTimePoint& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::time::SteadyClockTimePoint>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISteadyClock::GetInternalOffset(OUT nn::TimeSpanType& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISteadyClock::GetRtcValue(OUT int64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISteadyClock::GetSetupResutltValue(OUT uint32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISteadyClock::GetTestOffset(OUT nn::TimeSpanType& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISteadyClock::IsRtcResetDetected(OUT bool& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISteadyClock::SetInternalOffset(IN nn::TimeSpanType _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISteadyClock::SetTestOffset(IN nn::TimeSpanType _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISystemClock::GetCurrentTime(OUT nn::time::PosixTime& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISystemClock::GetSystemClockContext(OUT nn::time::SystemClockContext& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::time::SystemClockContext>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISystemClock::SetCurrentTime(IN nn::time::PosixTime _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ISystemClock::SetSystemClockContext(IN nn::time::SystemClockContext _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ITimeZoneService::GetDeviceLocationName(OUT nn::time::LocationName& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::time::LocationName>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ITimeZoneService::GetTimeZoneRuleVersion(OUT nn::time::TimeZoneRuleVersion& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ITimeZoneService::GetTotalLocationNameCount(OUT int32_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ITimeZoneService::LoadLocationNameList(IN int32_t _0, OUT int32_t& _1, OUT nn::time::LocationName * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::timesrv::detail::service::ITimeZoneService::LoadTimeZoneRule(IN nn::time::LocationName _0, OUT nn::time::TimeZoneRule * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x16, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::timesrv::detail::service::ITimeZoneService::SetDeviceLocationName(IN nn::time::LocationName _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ITimeZoneService::ToCalendarTime(IN nn::time::PosixTime _0, IN nn::time::TimeZoneRule * _1, guint _1_size, OUT nn::time::CalendarTime& _2, OUT nn::time::sf::CalendarAdditionalInfo& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x15, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto temp4 = resp.getDataPointer<nn::time::sf::CalendarAdditionalInfo>(0x10);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::timesrv::detail::service::ITimeZoneService::ToCalendarTimeWithMyRule(IN nn::time::PosixTime _0, OUT nn::time::CalendarTime& _1, OUT nn::time::sf::CalendarAdditionalInfo& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<nn::time::sf::CalendarAdditionalInfo>(0x10);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::timesrv::detail::service::ITimeZoneService::ToPosixTime(IN nn::time::CalendarTime _0, IN nn::time::TimeZoneRule * _1, guint _1_size, OUT int32_t& _2, OUT nn::time::PosixTime * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x15, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0xa, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::timesrv::detail::service::ITimeZoneService::ToPosixTimeWithMyRule(IN nn::time::CalendarTime _0, OUT int32_t& _1, OUT nn::time::PosixTime * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0xa, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::tma {
	class IHtcManager {
	public:
		IHtcManager();
		uint32_t Unknown0(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size);
		uint32_t Unknown1(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1);
		uint32_t Unknown2(OUT KObject * _0);
		uint32_t Unknown3(OUT KObject * _0);
		uint32_t Unknown4(OUT KObject * _0);
		uint32_t Unknown5(OUT KObject * _0);
		uint32_t Unknown6(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown7(OUT uint8_t * _0, guint _0_size);
		uint32_t Unknown8(IN uint8_t _0);
	};
	class IHtcsManager {
	public:
		IHtcsManager();
		uint32_t Unknown0(OUT uint32_t& _0, OUT uint32_t& _1);
		uint32_t Unknown1(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2);
		uint32_t Unknown10(OUT uint8_t * _0);
		uint32_t Unknown100(IN uint64_t _0, IN gpid _1);
		uint32_t Unknown101(IN uint64_t _0, IN gpid _1);
		uint32_t Unknown11(OUT uint8_t * _0);
		uint32_t Unknown12(OUT uint32_t& _0, OUT IUnknown * _1);
		uint32_t Unknown13(IN uint8_t _0, OUT uint32_t& _1, OUT IUnknown * _2);
		uint32_t Unknown2(IN uint8_t * _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown3(IN uint8_t * _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown4(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown5(IN uint32_t _0, OUT uint8_t * _1, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown6(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint64_t& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t Unknown7(IN uint32_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size, OUT uint32_t& _3, OUT uint64_t& _4);
		uint32_t Unknown8(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown9(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, OUT uint32_t& _3, OUT uint32_t& _4);
	};
	class ISocket {
	public:
		ISocket();
		uint32_t Unknown0(OUT uint32_t& _0, OUT uint32_t& _1);
		uint32_t Unknown1(IN uint8_t * _0, OUT uint32_t& _1, OUT uint32_t& _2);
		uint32_t Unknown10(IN uint32_t _0, OUT uint8_t * _1, OUT uint32_t& _2, OUT IUnknown * _3);
		uint32_t Unknown11(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT KObject * _3);
		uint32_t Unknown12(IN uint32_t _0, OUT uint32_t& _1, OUT uint64_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t Unknown13(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint64_t _3, IN KObject * _4, OUT uint32_t& _5, OUT KObject * _6);
		uint32_t Unknown14(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT KObject * _3);
		uint32_t Unknown15(IN uint32_t _0, IN uint64_t _1, IN KObject * _2, IN uint8_t * _3, guint _3_size, IN uint8_t * _4, guint _4_size, OUT uint32_t& _5, OUT KObject * _6);
		uint32_t Unknown16(IN uint32_t _0, OUT uint32_t& _1, OUT uint64_t& _2);
		uint32_t Unknown2(IN uint8_t * _0, OUT uint32_t& _1, OUT uint32_t& _2);
		uint32_t Unknown3(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2);
		uint32_t Unknown4(OUT uint8_t * _0, OUT uint32_t& _1, OUT IUnknown * _2);
		uint32_t Unknown5(IN uint32_t _0, OUT uint32_t& _1, OUT uint64_t& _2, OUT uint8_t * _3, guint _3_size);
		uint32_t Unknown6(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint64_t& _3);
		uint32_t Unknown7(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2);
		uint32_t Unknown8(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3);
		uint32_t Unknown9(OUT uint32_t& _0, OUT KObject * _1);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::tma::IHtcManager::Unknown0(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1, OUT uint8_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nn::tma::IHtcManager::Unknown1(IN uint8_t * _0, guint _0_size, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::tma::IHtcManager::Unknown2(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::tma::IHtcManager::Unknown3(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::tma::IHtcManager::Unknown4(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::tma::IHtcManager::Unknown5(OUT KObject * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::tma::IHtcManager::Unknown6(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::tma::IHtcManager::Unknown7(OUT uint8_t * _0, guint _0_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::tma::IHtcManager::Unknown8(IN uint8_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown0(OUT uint32_t& _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown1(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown10(OUT uint8_t * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown100(IN uint64_t _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown101(IN uint64_t _0, IN gpid _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown11(OUT uint8_t * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown12(OUT uint32_t& _0, OUT IUnknown * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown13(IN uint8_t _0, OUT uint32_t& _1, OUT IUnknown * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown2(IN uint8_t * _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown3(IN uint8_t * _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown4(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown5(IN uint32_t _0, OUT uint8_t * _1, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown6(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint64_t& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown7(IN uint32_t _0, IN uint32_t _1, IN uint8_t * _2, guint _2_size, OUT uint32_t& _3, OUT uint64_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown8(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::IHtcsManager::Unknown9(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, OUT uint32_t& _3, OUT uint32_t& _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::ISocket::Unknown0(OUT uint32_t& _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::ISocket::Unknown1(IN uint8_t * _0, OUT uint32_t& _1, OUT uint32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::ISocket::Unknown10(IN uint32_t _0, OUT uint8_t * _1, OUT uint32_t& _2, OUT IUnknown * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	_3 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::tma::ISocket::Unknown11(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT KObject * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::tma::ISocket::Unknown12(IN uint32_t _0, OUT uint32_t& _1, OUT uint64_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::tma::ISocket::Unknown13(IN uint32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint64_t _3, IN KObject * _4, OUT uint32_t& _5, OUT KObject * _6) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::tma::ISocket::Unknown14(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT KObject * _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	shared_ptr<KObject> temp4;
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	if(temp4 != nullptr)
		resp.copy(0, ctu->newHandle(temp4));
	return ret;
}
uint32_t nn::tma::ISocket::Unknown15(IN uint32_t _0, IN uint64_t _1, IN KObject * _2, IN uint8_t * _3, guint _3_size, IN uint8_t * _4, guint _4_size, OUT uint32_t& _5, OUT KObject * _6) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x21, 1, temp5);
	ctu->cpu.readmem(temp4, temp6, temp5);
	shared_ptr<KObject> temp7;
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	delete[] temp6;
	if(temp7 != nullptr)
		resp.copy(0, ctu->newHandle(temp7));
	return ret;
}
uint32_t nn::tma::ISocket::Unknown16(IN uint32_t _0, OUT uint32_t& _1, OUT uint64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::ISocket::Unknown2(IN uint8_t * _0, OUT uint32_t& _1, OUT uint32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::ISocket::Unknown3(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::ISocket::Unknown4(OUT uint8_t * _0, OUT uint32_t& _1, OUT IUnknown * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto temp1 = resp.getDataPointer<uint8_t *>(8);
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new IUnknown(resp.move_handles[0]);
	return ret;
}
uint32_t nn::tma::ISocket::Unknown5(IN uint32_t _0, OUT uint32_t& _1, OUT uint64_t& _2, OUT uint8_t * _3, guint _3_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x22, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::tma::ISocket::Unknown6(IN uint32_t _0, IN uint8_t * _1, guint _1_size, OUT uint32_t& _2, OUT uint64_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	return ret;
}
uint32_t nn::tma::ISocket::Unknown7(IN uint32_t _0, OUT uint32_t& _1, OUT uint32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::ISocket::Unknown8(IN uint32_t _0, IN uint32_t _1, OUT uint32_t& _2, OUT uint32_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::tma::ISocket::Unknown9(OUT uint32_t& _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::ts::server {
	class IMeasurementServer {
	public:
		IMeasurementServer();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::ts::server::IMeasurementServer::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ts::server::IMeasurementServer::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ts::server::IMeasurementServer::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::ts::server::IMeasurementServer::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::uart {
	class IManager {
	public:
		IManager();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
	};
	class IPortSession {
	public:
		IPortSession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::uart::IManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IManager::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IManager::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IManager::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IManager::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IManager::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IManager::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IManager::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IPortSession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IPortSession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IPortSession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IPortSession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IPortSession::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IPortSession::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IPortSession::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::uart::IPortSession::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::usb::ds {
	class IDsEndpoint {
	public:
		IDsEndpoint();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
	};
	class IDsInterface {
	public:
		IDsInterface();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
	class IDsService {
	public:
		IDsService();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::usb::ds::IDsEndpoint::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsEndpoint::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsEndpoint::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsEndpoint::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsEndpoint::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsEndpoint::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsInterface::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsService::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsService::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsService::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsService::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsService::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::ds::IDsService::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::usb::hs {
	class IClientEpSession {
	public:
		IClientEpSession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
	};
	class IClientIfSession {
	public:
		IClientIfSession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
	class IClientRootSession {
	public:
		IClientRootSession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::usb::hs::IClientEpSession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientEpSession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientEpSession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientEpSession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientEpSession::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientEpSession::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientEpSession::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientIfSession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientIfSession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientIfSession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientIfSession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientIfSession::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientIfSession::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientIfSession::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientIfSession::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientIfSession::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientIfSession::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientRootSession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientRootSession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientRootSession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientRootSession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientRootSession::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientRootSession::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientRootSession::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::hs::IClientRootSession::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::usb::pd::detail {
	class IPdCradleManager {
	public:
		IPdCradleManager();
		uint32_t Unknown0();
	};
	class IPdCradleSession {
	public:
		IPdCradleSession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
	};
	class IPdManager {
	public:
		IPdManager();
		uint32_t Unknown0();
	};
	class IPdSession {
	public:
		IPdSession();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::usb::pd::detail::IPdCradleManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdCradleSession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdCradleSession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdCradleSession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdCradleSession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdCradleSession::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdCradleSession::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdCradleSession::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdCradleSession::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdCradleSession::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdSession::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdSession::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdSession::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdSession::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdSession::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdSession::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pd::detail::IPdSession::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::usb::pm {
	class IPmService {
	public:
		IPmService();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::usb::pm::IPmService::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pm::IPmService::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pm::IPmService::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pm::IPmService::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pm::IPmService::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::usb::pm::IPmService::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::visrv::sf {
	class IApplicationDisplayService {
	public:
		IApplicationDisplayService();
		uint32_t CloseDisplay(IN uint64_t _0);
		uint32_t CloseLayer(IN uint64_t _0);
		uint32_t CreateStrayLayer(IN uint32_t _0, IN uint64_t _1, OUT uint64_t& _2, OUT int64_t& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t DestroyStrayLayer(IN uint64_t _0);
		uint32_t GetDisplayResolution(IN uint64_t _0, OUT int64_t& _1, OUT int64_t& _2);
		uint32_t GetDisplayVsyncEvent(IN uint64_t _0, OUT KObject * _1);
		uint32_t GetDisplayVsyncEventForDebug(IN uint64_t _0, OUT KObject * _1);
		uint32_t GetIndirectDisplayTransactionService(OUT nns::hosbinder::IHOSBinderDriver * _0);
		uint32_t GetIndirectLayerImageCropMap(IN float32_t _0, IN float32_t _1, IN float32_t _2, IN float32_t _3, IN int64_t _4, IN int64_t _5, IN uint64_t _6, IN nn::applet::AppletResourceUserId _7, IN gpid _8, OUT int64_t& _9, OUT int64_t& _10, OUT uint8_t * _11, guint _11_size);
		uint32_t GetIndirectLayerImageMap(IN int64_t _0, IN int64_t _1, IN uint64_t _2, IN nn::applet::AppletResourceUserId _3, IN gpid _4, OUT int64_t& _5, OUT int64_t& _6, OUT uint8_t * _7, guint _7_size);
		uint32_t GetIndirectLayerImageRequiredMemoryInfo(IN int64_t _0, IN int64_t _1, OUT int64_t& _2, OUT int64_t& _3);
		uint32_t GetManagerDisplayService(OUT nn::visrv::sf::IManagerDisplayService * _0);
		uint32_t GetRelayService(OUT nns::hosbinder::IHOSBinderDriver * _0);
		uint32_t GetSystemDisplayService(OUT nn::visrv::sf::ISystemDisplayService * _0);
		uint32_t ListDisplays(OUT int64_t& _0, OUT nn::vi::DisplayInfo * _1, guint _1_size);
		uint32_t OpenDefaultDisplay(OUT uint64_t& _0);
		uint32_t OpenDisplay(IN nn::vi::DisplayName _0, OUT uint64_t& _1);
		uint32_t OpenLayer(IN nn::vi::DisplayName _0, IN uint64_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3, OUT int64_t& _4, OUT uint8_t * _5, guint _5_size);
		uint32_t SetDisplayEnabled(IN bool _0, IN uint64_t _1);
		uint32_t SetLayerScalingMode(IN uint32_t _0, IN uint64_t _1);
	};
	class IApplicationRootService {
	public:
		IApplicationRootService();
		uint32_t GetDisplayService(IN uint32_t _0, OUT nn::visrv::sf::IApplicationDisplayService * _1);
	};
	class IManagerDisplayService {
	public:
		IManagerDisplayService();
		uint32_t AcquireLayerTexturePresentingEvent(IN uint64_t _0, OUT KObject * _1);
		uint32_t AddToLayerStack(IN uint32_t _0, IN uint64_t _1);
		uint32_t CreateIndirectConsumerEndPoint(IN uint64_t _0, IN nn::applet::AppletResourceUserId _1, OUT uint64_t& _2);
		uint32_t CreateIndirectLayer(OUT uint64_t& _0);
		uint32_t CreateIndirectProducerEndPoint(IN uint64_t _0, IN nn::applet::AppletResourceUserId _1, OUT uint64_t& _2);
		uint32_t CreateManagedLayer(IN uint32_t _0, IN uint64_t _1, IN nn::applet::AppletResourceUserId _2, OUT uint64_t& _3);
		uint32_t DestroyIndirectConsumerEndPoint(IN uint64_t _0);
		uint32_t DestroyIndirectLayer(IN uint64_t _0);
		uint32_t DestroyIndirectProducerEndPoint(IN uint64_t _0);
		uint32_t DestroyManagedLayer(IN uint64_t _0);
		uint32_t GetDisplayHotplugEvent(IN uint64_t _0, OUT KObject * _1);
		uint32_t GetDisplayHotplugState(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t GetDisplayResolution(IN uint64_t _0, OUT int64_t& _1, OUT int64_t& _2);
		uint32_t ReleaseLayerTexturePresentingEvent(IN uint64_t _0);
		uint32_t RemoveFromLayerStack(IN uint32_t _0, IN uint64_t _1);
		uint32_t SetConductorLayer(IN bool _0, IN uint64_t _1);
		uint32_t SetContentVisibility(IN bool _0);
		uint32_t SetDisplayAlpha(IN float32_t _0, IN uint64_t _1);
		uint32_t SetDisplayLayerStack(IN uint32_t _0, IN uint64_t _1);
		uint32_t SetDisplayPowerState(IN uint32_t _0, IN uint64_t _1);
		uint32_t SetIndirectProducerFlipOffset(IN uint64_t _0, IN uint64_t _1, IN nn::TimeSpan _2);
		uint32_t SetLayerVisibility(IN bool _0, IN uint64_t _1);
	};
	class IManagerRootService {
	public:
		IManagerRootService();
		uint32_t GetDisplayService(IN uint32_t _0, OUT nn::visrv::sf::IApplicationDisplayService * _1);
		uint32_t GetDisplayServiceWithProxyNameExchange(IN nn::vi::ProxyName _0, IN uint32_t _1, OUT nn::visrv::sf::IApplicationDisplayService * _2);
	};
	class ISystemDisplayService {
	public:
		ISystemDisplayService();
		uint32_t CloseIndirectLayer(IN uint64_t _0);
		uint32_t CreateStrayLayer(IN uint32_t _0, IN uint64_t _1, OUT uint64_t& _2, OUT int64_t& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t FlipIndirectLayer(IN uint64_t _0);
		uint32_t GetDisplayCmuLuma(IN uint64_t _0, OUT float32_t& _1);
		uint32_t GetDisplayCmuMode(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t GetDisplayContentType(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t GetDisplayContrastRatio(IN uint64_t _0, OUT float32_t& _1);
		uint32_t GetDisplayGamma(IN uint64_t _0, OUT float32_t& _1);
		uint32_t GetDisplayLogicalResolution(IN uint64_t _0, OUT int32_t& _1, OUT int32_t& _2);
		uint32_t GetDisplayMode(IN uint64_t _0, OUT nn::vi::DisplayModeInfo& _1);
		uint32_t GetDisplayRgbRange(IN uint64_t _0, OUT uint32_t& _1);
		uint32_t GetDisplayUnderscan(IN uint64_t _0, OUT int64_t& _1);
		uint32_t GetLayerZ(IN uint64_t _0, OUT int64_t& _1);
		uint32_t GetZOrderCountMax(IN uint64_t _0, OUT int64_t& _1);
		uint32_t GetZOrderCountMin(IN uint64_t _0, OUT int64_t& _1);
		uint32_t ListDisplayContentTypes(IN uint64_t _0, OUT int64_t& _1, OUT uint32_t * _2, guint _2_size);
		uint32_t ListDisplayModes(IN uint64_t _0, OUT int64_t& _1, OUT nn::vi::DisplayModeInfo * _2, guint _2_size);
		uint32_t ListDisplayRgbRanges(IN uint64_t _0, OUT int64_t& _1, OUT uint32_t * _2, guint _2_size);
		uint32_t OpenIndirectLayer(IN uint64_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT int64_t& _3, OUT uint8_t * _4, guint _4_size);
		uint32_t SetDisplayCmuLuma(IN float32_t _0, IN uint64_t _1);
		uint32_t SetDisplayCmuMode(IN uint32_t _0, IN uint64_t _1);
		uint32_t SetDisplayContentType(IN uint32_t _0, IN uint64_t _1);
		uint32_t SetDisplayContrastRatio(IN float32_t _0, IN uint64_t _1);
		uint32_t SetDisplayGamma(IN float32_t _0, IN uint64_t _1);
		uint32_t SetDisplayMagnification(IN int32_t _0, IN int32_t _1, IN int32_t _2, IN int32_t _3, IN uint64_t _4);
		uint32_t SetDisplayMode(IN uint64_t _0, IN nn::vi::DisplayModeInfo _1);
		uint32_t SetDisplayRgbRange(IN uint32_t _0, IN uint64_t _1);
		uint32_t SetDisplayUnderscan(IN uint64_t _0, IN int64_t _1);
		uint32_t SetLayerAlpha(IN float32_t _0, IN uint64_t _1);
		uint32_t SetLayerPosition(IN float32_t _0, IN float32_t _1, IN uint64_t _2);
		uint32_t SetLayerSize(IN uint64_t _0, IN int64_t _1, IN int64_t _2);
		uint32_t SetLayerVisibility(IN bool _0, IN uint64_t _1);
		uint32_t SetLayerZ(IN uint64_t _0, IN int64_t _1);
	};
	class ISystemRootService {
	public:
		ISystemRootService();
		uint32_t GetDisplayService(IN uint32_t _0, OUT nn::visrv::sf::IApplicationDisplayService * _1);
		uint32_t GetDisplayServiceWithProxyNameExchange(IN nn::vi::ProxyName _0, IN uint32_t _1, OUT nn::visrv::sf::IApplicationDisplayService * _2);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::visrv::sf::IApplicationDisplayService::CloseDisplay(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::CloseLayer(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::CreateStrayLayer(IN uint32_t _0, IN uint64_t _1, OUT uint64_t& _2, OUT int64_t& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::DestroyStrayLayer(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::GetDisplayResolution(IN uint64_t _0, OUT int64_t& _1, OUT int64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::GetDisplayVsyncEvent(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::GetDisplayVsyncEventForDebug(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::GetIndirectDisplayTransactionService(OUT nns::hosbinder::IHOSBinderDriver * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nns::hosbinder::IHOSBinderDriver(resp.move_handles[0]);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::GetIndirectLayerImageCropMap(IN float32_t _0, IN float32_t _1, IN float32_t _2, IN float32_t _3, IN int64_t _4, IN int64_t _5, IN uint64_t _6, IN nn::applet::AppletResourceUserId _7, IN gpid _8, OUT int64_t& _9, OUT int64_t& _10, OUT uint8_t * _11, guint _11_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x46, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::GetIndirectLayerImageMap(IN int64_t _0, IN int64_t _1, IN uint64_t _2, IN nn::applet::AppletResourceUserId _3, IN gpid _4, OUT int64_t& _5, OUT int64_t& _6, OUT uint8_t * _7, guint _7_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x46, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::GetIndirectLayerImageRequiredMemoryInfo(IN int64_t _0, IN int64_t _1, OUT int64_t& _2, OUT int64_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::GetManagerDisplayService(OUT nn::visrv::sf::IManagerDisplayService * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::visrv::sf::IManagerDisplayService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::GetRelayService(OUT nns::hosbinder::IHOSBinderDriver * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nns::hosbinder::IHOSBinderDriver(resp.move_handles[0]);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::GetSystemDisplayService(OUT nn::visrv::sf::ISystemDisplayService * _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_0 OMG = new nn::visrv::sf::ISystemDisplayService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::ListDisplays(OUT int64_t& _0, OUT nn::vi::DisplayInfo * _1, guint _1_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::OpenDefaultDisplay(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::OpenDisplay(IN nn::vi::DisplayName _0, OUT uint64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::OpenLayer(IN nn::vi::DisplayName _0, IN uint64_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3, OUT int64_t& _4, OUT uint8_t * _5, guint _5_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::SetDisplayEnabled(IN bool _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationDisplayService::SetLayerScalingMode(IN uint32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IApplicationRootService::GetDisplayService(IN uint32_t _0, OUT nn::visrv::sf::IApplicationDisplayService * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::visrv::sf::IApplicationDisplayService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::AcquireLayerTexturePresentingEvent(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::AddToLayerStack(IN uint32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::CreateIndirectConsumerEndPoint(IN uint64_t _0, IN nn::applet::AppletResourceUserId _1, OUT uint64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::CreateIndirectLayer(OUT uint64_t& _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::CreateIndirectProducerEndPoint(IN uint64_t _0, IN nn::applet::AppletResourceUserId _1, OUT uint64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::CreateManagedLayer(IN uint32_t _0, IN uint64_t _1, IN nn::applet::AppletResourceUserId _2, OUT uint64_t& _3) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::DestroyIndirectConsumerEndPoint(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::DestroyIndirectLayer(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::DestroyIndirectProducerEndPoint(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::DestroyManagedLayer(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::GetDisplayHotplugEvent(IN uint64_t _0, OUT KObject * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::GetDisplayHotplugState(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::GetDisplayResolution(IN uint64_t _0, OUT int64_t& _1, OUT int64_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::ReleaseLayerTexturePresentingEvent(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::RemoveFromLayerStack(IN uint32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::SetConductorLayer(IN bool _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::SetContentVisibility(IN bool _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::SetDisplayAlpha(IN float32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::SetDisplayLayerStack(IN uint32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::SetDisplayPowerState(IN uint32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::SetIndirectProducerFlipOffset(IN uint64_t _0, IN uint64_t _1, IN nn::TimeSpan _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerDisplayService::SetLayerVisibility(IN bool _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::IManagerRootService::GetDisplayService(IN uint32_t _0, OUT nn::visrv::sf::IApplicationDisplayService * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::visrv::sf::IApplicationDisplayService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::visrv::sf::IManagerRootService::GetDisplayServiceWithProxyNameExchange(IN nn::vi::ProxyName _0, IN uint32_t _1, OUT nn::visrv::sf::IApplicationDisplayService * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::visrv::sf::IApplicationDisplayService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::CloseIndirectLayer(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::CreateStrayLayer(IN uint32_t _0, IN uint64_t _1, OUT uint64_t& _2, OUT int64_t& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::FlipIndirectLayer(IN uint64_t _0) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetDisplayCmuLuma(IN uint64_t _0, OUT float32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetDisplayCmuMode(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetDisplayContentType(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetDisplayContrastRatio(IN uint64_t _0, OUT float32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetDisplayGamma(IN uint64_t _0, OUT float32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetDisplayLogicalResolution(IN uint64_t _0, OUT int32_t& _1, OUT int32_t& _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetDisplayMode(IN uint64_t _0, OUT nn::vi::DisplayModeInfo& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetDisplayRgbRange(IN uint64_t _0, OUT uint32_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetDisplayUnderscan(IN uint64_t _0, OUT int64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetLayerZ(IN uint64_t _0, OUT int64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetZOrderCountMax(IN uint64_t _0, OUT int64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::GetZOrderCountMin(IN uint64_t _0, OUT int64_t& _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::ListDisplayContentTypes(IN uint64_t _0, OUT int64_t& _1, OUT uint32_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::ListDisplayModes(IN uint64_t _0, OUT int64_t& _1, OUT nn::vi::DisplayModeInfo * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::ListDisplayRgbRanges(IN uint64_t _0, OUT int64_t& _1, OUT uint32_t * _2, guint _2_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::OpenIndirectLayer(IN uint64_t _0, IN nn::applet::AppletResourceUserId _1, IN gpid _2, OUT int64_t& _3, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(6, 0, temp2);
	auto ret = ipc_send(session, &req, &resp);
	ctu->cpu.writemem(temp1, temp3, temp2);
	delete[] temp3;
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetDisplayCmuLuma(IN float32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetDisplayCmuMode(IN uint32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetDisplayContentType(IN uint32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetDisplayContrastRatio(IN float32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetDisplayGamma(IN float32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetDisplayMagnification(IN int32_t _0, IN int32_t _1, IN int32_t _2, IN int32_t _3, IN uint64_t _4) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetDisplayMode(IN uint64_t _0, IN nn::vi::DisplayModeInfo _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetDisplayRgbRange(IN uint32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetDisplayUnderscan(IN uint64_t _0, IN int64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetLayerAlpha(IN float32_t _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetLayerPosition(IN float32_t _0, IN float32_t _1, IN uint64_t _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetLayerSize(IN uint64_t _0, IN int64_t _1, IN int64_t _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetLayerVisibility(IN bool _0, IN uint64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemDisplayService::SetLayerZ(IN uint64_t _0, IN int64_t _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::visrv::sf::ISystemRootService::GetDisplayService(IN uint32_t _0, OUT nn::visrv::sf::IApplicationDisplayService * _1) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_1 OMG = new nn::visrv::sf::IApplicationDisplayService(resp.move_handles[0]);
	return ret;
}
uint32_t nn::visrv::sf::ISystemRootService::GetDisplayServiceWithProxyNameExchange(IN nn::vi::ProxyName _0, IN uint32_t _1, OUT nn::visrv::sf::IApplicationDisplayService * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	_2 OMG = new nn::visrv::sf::IApplicationDisplayService(resp.move_handles[0]);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::wlan::detail {
	class IInfraManager {
	public:
		IInfraManager();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown14();
		uint32_t Unknown15();
		uint32_t Unknown16();
		uint32_t Unknown17();
		uint32_t Unknown18();
		uint32_t Unknown19();
		uint32_t Unknown2();
		uint32_t Unknown20();
		uint32_t Unknown21();
		uint32_t Unknown22();
		uint32_t Unknown23();
		uint32_t Unknown24();
		uint32_t Unknown25();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
	class ILocalGetActionFrame {
	public:
		ILocalGetActionFrame();
		uint32_t Unknown0();
	};
	class ILocalGetFrame {
	public:
		ILocalGetFrame();
		uint32_t Unknown0();
	};
	class ILocalManager {
	public:
		ILocalManager();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown14();
		uint32_t Unknown15();
		uint32_t Unknown16();
		uint32_t Unknown17();
		uint32_t Unknown18();
		uint32_t Unknown19();
		uint32_t Unknown2();
		uint32_t Unknown20();
		uint32_t Unknown21();
		uint32_t Unknown22();
		uint32_t Unknown23();
		uint32_t Unknown24();
		uint32_t Unknown25();
		uint32_t Unknown26();
		uint32_t Unknown27();
		uint32_t Unknown28();
		uint32_t Unknown29();
		uint32_t Unknown3();
		uint32_t Unknown30();
		uint32_t Unknown31();
		uint32_t Unknown32();
		uint32_t Unknown33();
		uint32_t Unknown34();
		uint32_t Unknown35();
		uint32_t Unknown36();
		uint32_t Unknown37();
		uint32_t Unknown38();
		uint32_t Unknown39();
		uint32_t Unknown4();
		uint32_t Unknown40();
		uint32_t Unknown41();
		uint32_t Unknown42();
		uint32_t Unknown43();
		uint32_t Unknown44();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
	class ISocketGetFrame {
	public:
		ISocketGetFrame();
		uint32_t Unknown0();
	};
	class ISocketManager {
	public:
		ISocketManager();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::wlan::detail::IInfraManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown14() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown15() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown16() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown17() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown18() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown19() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown20() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown21() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown22() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown23() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown24() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown25() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::IInfraManager::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalGetActionFrame::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalGetFrame::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown14() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown15() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown16() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown17() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown18() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown19() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown20() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown21() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown22() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown23() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown24() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown25() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown26() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown27() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown28() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown29() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown30() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown31() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown32() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown33() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown34() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown35() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown36() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown37() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown38() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown39() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown40() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown41() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown42() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown43() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown44() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ILocalManager::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketGetFrame::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::wlan::detail::ISocketManager::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nn::xcd::detail {
	class ISystemServer {
	public:
		ISystemServer();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown101();
		uint32_t Unknown102();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown14();
		uint32_t Unknown15();
		uint32_t Unknown16();
		uint32_t Unknown17();
		uint32_t Unknown18();
		uint32_t Unknown19();
		uint32_t Unknown2();
		uint32_t Unknown20();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nn::xcd::detail::ISystemServer::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown101() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown102() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown14() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown15() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown16() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown17() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown18() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown19() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown20() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nn::xcd::detail::ISystemServer::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nns::hosbinder {
	class IHOSBinderDriver {
	public:
		IHOSBinderDriver();
		uint32_t AdjustRefcount(IN int32_t _0, IN int32_t _1, IN int32_t _2);
		uint32_t GetNativeHandle(IN int32_t _0, IN uint32_t _1, OUT KObject * _2);
		uint32_t TransactParcel(IN int32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, OUT uint8_t * _4, guint _4_size);
		uint32_t TransactParcelAuto(IN int32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, OUT uint8_t * _4, guint _4_size);
	};
}
#ifdef DEFINE_CALLERS
uint32_t nns::hosbinder::IHOSBinderDriver::AdjustRefcount(IN int32_t _0, IN int32_t _1, IN int32_t _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::hosbinder::IHOSBinderDriver::GetNativeHandle(IN int32_t _0, IN uint32_t _1, OUT KObject * _2) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	shared_ptr<KObject> temp1;
	auto ret = ipc_send(session, &req, &resp);
	if(temp1 != nullptr)
		resp.copy(0, ctu->newHandle(temp1));
	return ret;
}
uint32_t nns::hosbinder::IHOSBinderDriver::TransactParcel(IN int32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(5, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(6, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
uint32_t nns::hosbinder::IHOSBinderDriver::TransactParcelAuto(IN int32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, OUT uint8_t * _4, guint _4_size) {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	guint temp2;
	auto temp1 = req.getBuffer(0x21, 0, temp2);
	ctu->cpu.readmem(temp1, temp3, temp2);
	guint temp5;
	auto temp4 = req.getBuffer(0x22, 0, temp5);
	auto ret = ipc_send(session, &req, &resp);
	delete[] temp3;
	ctu->cpu.writemem(temp4, temp6, temp5);
	delete[] temp6;
	return ret;
}
#endif // DEFINE_CALLERS
namespace nns::nvdrv {
	class INvDrvDebugFSServices {
	public:
		INvDrvDebugFSServices();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
	};
	class INvDrvServices {
	public:
		INvDrvServices();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown10();
		uint32_t Unknown11();
		uint32_t Unknown12();
		uint32_t Unknown13();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
		uint32_t Unknown8();
		uint32_t Unknown9();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nns::nvdrv::INvDrvDebugFSServices::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvDebugFSServices::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvDebugFSServices::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvDebugFSServices::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvDebugFSServices::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown10() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown11() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown12() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown13() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown8() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nns::nvdrv::INvDrvServices::Unknown9() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nv::gemcontrol {
	class INvGemControl {
	public:
		INvGemControl();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
		uint32_t Unknown3();
		uint32_t Unknown4();
		uint32_t Unknown5();
		uint32_t Unknown6();
		uint32_t Unknown7();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nv::gemcontrol::INvGemControl::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nv::gemcontrol::INvGemControl::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nv::gemcontrol::INvGemControl::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nv::gemcontrol::INvGemControl::Unknown3() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nv::gemcontrol::INvGemControl::Unknown4() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nv::gemcontrol::INvGemControl::Unknown5() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nv::gemcontrol::INvGemControl::Unknown6() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nv::gemcontrol::INvGemControl::Unknown7() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
namespace nv::gemcoredump {
	class INvGemCoreDump {
	public:
		INvGemCoreDump();
		uint32_t Unknown0();
		uint32_t Unknown1();
		uint32_t Unknown2();
	};
}
#ifdef DEFINE_CALLERS
uint32_t nv::gemcoredump::INvGemCoreDump::Unknown0() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nv::gemcoredump::INvGemCoreDump::Unknown1() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
uint32_t nv::gemcoredump::INvGemCoreDump::Unknown2() {
	ipc_request_t req;
	ipc_response_t resp;
	memset(&req, 0, sizeof(ipc_request_t));
	auto ret = ipc_send(session, &req, &resp);
	return ret;
}
#endif // DEFINE_CALLERS
