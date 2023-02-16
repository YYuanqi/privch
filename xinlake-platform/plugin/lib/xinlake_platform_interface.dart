import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'types.dart';
import 'xinlake_platform_method_channel.dart';

abstract class XinlakePlatformInterface extends PlatformInterface {
  /// Constructs a XinlakePlatformPlatform.
  XinlakePlatformInterface() : super(token: _token);

  static final Object _token = Object();

  static XinlakePlatformInterface _instance = MethodChannelXinlakePlatform();

  /// The default instance of [XinlakePlatformInterface] to use.
  /// Defaults to [MethodChannelXinlakePlatform].
  static XinlakePlatformInterface get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [XinlakePlatformInterface] when
  /// they register themselves.
  static set instance(XinlakePlatformInterface instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<List<XinFile>?> pickFile(
    bool multiSelection,
    String fileTypes,
    // android
    XinAndroidAppDir? cacheDir,
    bool cacheOverwrite,
    // windows
    String? openPath,
    String? defaultPath,
    String? fileDescription,
  ) {
    throw UnimplementedError('not implemented');
  }

  Future<void> setNativeUiMode(
    XinUiMode mode,
    int darkColor,
    int lightColor,
    int animateMs,
  ) {
    throw UnimplementedError('not implemented');
  }

  Future<String?> getAppDir(XinAndroidAppDir? androidAppDir) {
    throw UnimplementedError('not implemented');
  }

  Future<XinVersionInfo?> getAppVersion(bool flutterStyle) {
    throw UnimplementedError('not implemented');
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('not implemented');
  }
}
