#ifndef __CC_WebView_INL_H_
#define __CC_WebView_INL_H_

#include "WebView.h"
#include "CCGLView.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"

namespace cocos2d {
namespace plugin {
WebView::WebView() : _impl(new WebViewImpl(this)) {
}

WebView::~WebView() {
    delete _impl;
}

WebView *WebView::create() {
    auto pRet = new WebView();
    if (pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    return nullptr;
}

void WebView::setJavascriptInterfaceScheme(const std::string &scheme) {
    _impl->setJavascriptInterfaceScheme(scheme);
}

void WebView::loadData(const cocos2d::Data &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL) {
    _impl->loadData(data, MIMEType, encoding, baseURL);
}

void WebView::loadHTMLString(const std::string &string, const std::string &baseURL) {
    _impl->loadHTMLString(string, baseURL);
}

void WebView::loadUrl(const std::string &url) {
    _impl->loadUrl(url);
}

void WebView::loadFile(const std::string &fileName) {
    _impl->loadFile(fileName);
}

void WebView::stopLoading() {
    _impl->stopLoading();
}

void WebView::reload() {
    _impl->reload();
}

bool WebView::canGoBack() {
    return _impl->canGoBack();
}

bool WebView::canGoForward() {
    return _impl->canGoForward();
}

void WebView::goBack() {
    _impl->goBack();
}

void WebView::goForward() {
    _impl->goForward();
}

void WebView::evaluateJS(const std::string &js) {
    _impl->evaluateJS(js);
}

void WebView::setScalesPageToFit(bool const scalesPageToFit) {
    _impl->setScalesPageToFit(scalesPageToFit);
}

void WebView::draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags) {
    cocos2d::ui::Widget::draw(renderer, transform, flags);
    _impl->draw(renderer, transform, flags);
}

void WebView::setVisible(bool visible) {
    Node::setVisible(visible);
    _impl->setVisible(visible);
}
} // namespace cocos2d
} // namespace plugin

#endif
