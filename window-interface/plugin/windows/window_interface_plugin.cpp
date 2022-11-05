#include "window_interface_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

#include <flutter/method_channel.h>
#include <flutter/event_channel.h>
#include <flutter/event_stream_handler_functions.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <map>
#include <memory>
#include <sstream>

/* full screen
 */
extern void getFullScreen(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

extern void setFullScreen(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

extern void toggleFullScreen(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

/* window placement
 */
extern void getWindowPlacement(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

extern void setWindowPlacement(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

/* min size
 */
extern void getWindowMinSize(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

extern void setWindowMinSize(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

extern void resetWindowMinSize(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

/* max size
 */
extern void getWindowMaxSize(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

extern void setWindowMaxSize(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

extern void resetWindowMaxSize(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

/* stay on top
 */
extern void setStayOnTop(const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

extern void initPlacement();

// event channel
extern void setEventSink(std::unique_ptr<flutter::EventSink<>>& eventSink);


namespace WindowInterface {

    // static
    void WindowInterfacePlugin::RegisterWithRegistrar(
        flutter::PluginRegistrarWindows* registrar) {
        auto plugin = std::make_unique<WindowInterfacePlugin>();

        auto eventHandler = std::make_unique<flutter::StreamHandlerFunctions<>>(
            [](const flutter::EncodableValue* arguments, std::unique_ptr<flutter::EventSink<>>&& events)
            -> std::unique_ptr<flutter::StreamHandlerError<>> {
                setEventSink(events);
                return nullptr;
            },
            [](const flutter::EncodableValue* arguments)
                -> std::unique_ptr<flutter::StreamHandlerError<>> {
                std::unique_ptr<flutter::EventSink<>> events = nullptr;
                setEventSink(events);
                return nullptr;
            });

        auto eventChannel = std::make_unique<flutter::EventChannel<flutter::EncodableValue>>(
            registrar->messenger(), "window_interface_event",
            &flutter::StandardMethodCodec::GetInstance());

        auto methodChannel = std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
            registrar->messenger(), "window_interface_method",
            &flutter::StandardMethodCodec::GetInstance());

        eventChannel->SetStreamHandler(std::move(eventHandler));
        methodChannel->SetMethodCallHandler(
            [plugin_pointer = plugin.get()](const auto& call, auto result) {
            plugin_pointer->HandleMethodCall(call, std::move(result));
        });

        registrar->AddPlugin(std::move(plugin));

        // initPlacement window placement
        initPlacement();
    }

    WindowInterfacePlugin::WindowInterfacePlugin() {}
    WindowInterfacePlugin::~WindowInterfacePlugin() {}

    void WindowInterfacePlugin::HandleMethodCall(
        const flutter::MethodCall<flutter::EncodableValue>& method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {

        const std::string method_name = method_call.method_name();
        if (method_name == "getFullScreen") {
            getFullScreen(method_call, std::move(result));
        } else if (method_name == "setFullScreen") {
            setFullScreen(method_call, std::move(result));
        } else if (method_name == "toggleFullScreen") {
            toggleFullScreen(method_call, std::move(result));
        } else if (method_name == "getWindowPlacement") {
            getWindowPlacement(method_call, std::move(result));
        } else if (method_name == "setWindowPlacement") {
            setWindowPlacement(method_call, std::move(result));
        } else if (method_name == "getWindowMinSize") {
            getWindowMinSize(method_call, std::move(result));
        } else if (method_name == "setWindowMinSize") {
            setWindowMinSize(method_call, std::move(result));
        } else if (method_name == "resetWindowMinSize") {
            resetWindowMinSize(method_call, std::move(result));
        } else if (method_name == "getWindowMaxSize") {
            getWindowMaxSize(method_call, std::move(result));
        } else if (method_name == "setWindowMaxSize") {
            setWindowMaxSize(method_call, std::move(result));
        } else if (method_name == "resetWindowMaxSize") {
            resetWindowMaxSize(method_call, std::move(result));
        } else if (method_name == "setStayOnTop") {
            setStayOnTop(method_call, std::move(result));
        } else {
            result->NotImplemented();
        }
    }
}  // namespace 
