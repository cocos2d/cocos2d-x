#ifndef DATAEQUALITYCHECKER_H
#define DATAEQUALITYCHECKER_H

#include "cocos2d.h"
#include <string>
#include <vector>

class DataEqualityChecker : public cocos2d::CCDataVisitor
{
public:
    DataEqualityChecker();

    bool check(cocos2d::CCObject *getLHS, cocos2d::CCObject *rhs);

    const std::vector<std::string> &trace() const;
    const std::string &printedLHS() const;
    const std::string &printedRHS() const;

protected:
    virtual void visitObject(const cocos2d::CCObject *p);

    virtual void visit(const cocos2d::CCBool *p);
    virtual void visit(const cocos2d::CCInteger *p);
    virtual void visit(const cocos2d::CCFloat *p);
    virtual void visit(const cocos2d::CCDouble *p);
    virtual void visit(const cocos2d::CCString *p);
    virtual void visit(const cocos2d::CCArray *p);
    virtual void visit(const cocos2d::CCDictionary *p);
    virtual void visit(const cocos2d::CCSet *p);

private:
    void pushToTrace(const cocos2d::CCString *message);
    cocos2d::CCObject *getLHS();
    void stopOnError(const cocos2d::CCObject *rhs);

    bool m_hasError;
    std::vector<std::string> m_trace;
    std::string m_printedLHS;
    std::string m_printedRHS;
    std::vector<cocos2d::CCObject *> m_lhsStack;
};

#endif // DATAEQUALITYCHECKER_H
