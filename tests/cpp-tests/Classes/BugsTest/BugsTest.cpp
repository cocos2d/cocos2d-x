#include "BugsTest.h"
#include "Bug-350.h"
#include "Bug-422.h"
#include "Bug-458/Bug-458.h"
#include "Bug-624.h"
#include "Bug-886.h"
#include "Bug-899.h"
#include "Bug-914.h"
#include "Bug-1159.h"
#include "Bug-1174.h"
#include "Bug-12847.h"
#include "Bug-Child.h"
#include "Bug-CCDrawNode.h"
#include "Bug-PageViewLayout.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "Bug-14327.h"
#endif

BugsTests::BugsTests()
{
    ADD_TEST_CASE(Bug350Layer);
    ADD_TEST_CASE(Bug422Layer);
    ADD_TEST_CASE(Bug458Layer);
    ADD_TEST_CASE(Bug624Layer);
    ADD_TEST_CASE(Bug886Layer);
    ADD_TEST_CASE(Bug899Layer);
    ADD_TEST_CASE(Bug914Layer);
    ADD_TEST_CASE(Bug1159Layer);
    ADD_TEST_CASE(Bug1174Layer);
    ADD_TEST_CASE(BugChild);
    ADD_TEST_CASE(BugCameraMask);
    ADD_TEST_CASE(BugDrawNodeLayer);
    ADD_TEST_CASE(BugPageViewLayer);
    ADD_TEST_CASE(Bug12847Layer);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    ADD_TEST_CASE(Bug14327Layer);
#endif
}
