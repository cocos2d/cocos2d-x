#include "CocoaDataEqualityChecker.h"

using namespace cocos2d;

DataEqualityChecker::DataEqualityChecker()
{
}

void DataEqualityChecker::visitObject(const CCObject *p)
{
    if (m_hasError)
        return;
    stopOnError(p);
}

void DataEqualityChecker::visit(const CCBool *p)
{
    if (m_hasError)
        return;
    if (const CCBool *left = dynamic_cast<const CCBool*>(getLHS())) {
        if (left->getValue() != p->getValue())
            stopOnError(p);
    } else {
        stopOnError(p);
    }
}

void DataEqualityChecker::visit(const CCInteger *p)
{
    if (m_hasError)
        return;
    if (const CCInteger *left = dynamic_cast<const CCInteger*>(getLHS())) {
        if (left->getValue() != p->getValue())
            stopOnError(p);
    } else {
        stopOnError(p);
    }
}

void DataEqualityChecker::visit(const CCFloat *p)
{
    if (m_hasError)
        return;
    if (const CCFloat *left = dynamic_cast<const CCFloat*>(getLHS())) {
        if (left->getValue() != p->getValue())
            stopOnError(p);
    } else {
        stopOnError(p);
    }
}

void DataEqualityChecker::visit(const CCDouble *p)
{
    if (m_hasError)
        return;
    if (const CCDouble *left = dynamic_cast<const CCDouble*>(getLHS())) {
        if (left->getValue() != p->getValue())
            stopOnError(p);
    } else {
        stopOnError(p);
    }
}

void DataEqualityChecker::visit(const CCString *p)
{
    if (m_hasError)
        return;
    if (const CCString *left = dynamic_cast<const CCString*>(getLHS())) {
        if (left->m_sString != p->m_sString)
            stopOnError(p);
    } else {
        stopOnError(p);
    }
}

void DataEqualityChecker::visit(const CCArray *p)
{
    if (m_hasError)
        return;
    if (CCArray *left = dynamic_cast<CCArray*>(getLHS())) {
        CCArray *right = const_cast<CCArray *>(p);
        if (left->count() != right->count()) {
            stopOnError(p);
        } else {
            for (int i = 0, n = right->count(); i < n; ++i) {
                pushToTrace(CCString::createWithFormat("Array member #%d", i));

                m_lhsStack.push_back(left->objectAtIndex(i));
                right->objectAtIndex(i)->acceptVisitor(*this);
                m_lhsStack.pop_back();
                m_trace.pop_back();
            }
        }
    } else {
        stopOnError(p);
    }
}

void DataEqualityChecker::visit(const CCDictionary *p)
{
    if (m_hasError)
        return;
    if (CCDictionary *left = dynamic_cast<CCDictionary*>(getLHS())) {
        CCDictionary *right = const_cast<CCDictionary *>(p);
        if (left->count() != right->count()) {
            stopOnError(p);
            return;
        }
        CCDictElement *element = 0;
        CCDICT_FOREACH(p, element) {
            CCObject *object = NULL;

            const std::string key = element->getStrKey();
            pushToTrace(CCString::createWithFormat("Dictionary key \"%s\"",
                                                   key.c_str()));
            object = left->objectForKey(key);
            if (!object) {
                stopOnError(p);
                return;
            }
            m_trace.pop_back();

            pushToTrace(CCString::createWithFormat("Dictionary object by key \"%s\"",
                                                   key.c_str()));
            m_lhsStack.push_back(object);
            element->getObject()->acceptVisitor(*this);
            m_lhsStack.pop_back();
            m_trace.pop_back();
        }
    } else {
        stopOnError(p);
    }
}

void DataEqualityChecker::visit(const CCSet *p)
{
    if (m_hasError)
        return;
    stopOnError(p);
}

void DataEqualityChecker::pushToTrace(const CCString *message)
{
    m_trace.push_back(message->m_sString);
    delete message;
}

CCObject *DataEqualityChecker::getLHS()
{
    return m_lhsStack.back();
}

void DataEqualityChecker::stopOnError(const CCObject *rhs)
{
    CCPrettyPrinter printer;

    if (getLHS()) {
        getLHS()->acceptVisitor(printer);
        m_printedLHS = printer.getResult();
    } else {
        m_printedLHS = "<null>";
    }

    if (rhs) {
        printer.clear();
        const_cast<CCObject *>(rhs)->acceptVisitor(printer);
        m_printedRHS = printer.getResult();
    } else {
        m_printedRHS = "<null>";
    }

    m_hasError = true;
}

bool DataEqualityChecker::check(CCObject *lhs, CCObject *rhs)
{
    m_lhsStack.push_back(lhs);

    m_hasError = false;
    rhs->acceptVisitor(*this);
    if (m_hasError)
        return false;

    return true;
}

const std::vector<std::string> &DataEqualityChecker::trace() const
{
    return m_trace;
}

const std::string &DataEqualityChecker::printedLHS() const
{
    return m_printedLHS;
}

const std::string &DataEqualityChecker::printedRHS() const
{
    return m_printedRHS;
}
