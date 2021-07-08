#include "ut_simplelistmodel.h"

Ut_SimpleListModel::Ut_SimpleListModel()
{

}

void Ut_SimpleListModel::SetUp()
{
    m_simpleListModel = new SimpleListModel();
}

void Ut_SimpleListModel::TearDown()
{
    delete m_simpleListModel;
}

TEST_F(Ut_SimpleListModel, data)
{
    m_simpleListModel->appendText("1", true);
    m_simpleListModel->appendText("2", true);
    m_simpleListModel->appendText("3", true);
    m_simpleListModel->data(m_simpleListModel->index(1, 0), 7);
    m_simpleListModel->data(m_simpleListModel->index(1, 0), SimpleListModel::Role::ExpressionCount);
    m_simpleListModel->data(m_simpleListModel->index(1, 0), SimpleListModel::Role::ExpressionPrevious);
    ASSERT_EQ(m_simpleListModel->data(m_simpleListModel->index(1, 0), SimpleListModel::Role::ExpressionNext), "3");
    DSettingsAlt::deleteInstance();
}

TEST_F(Ut_SimpleListModel, updataList1)
{
    for (int i = 0; i < 500; i++) {
        m_simpleListModel->m_expressionList.append("1");
    }
    m_simpleListModel->updataList("2", 500, true);
    m_simpleListModel->updataList("3", 500, false);
    m_simpleListModel->updataList("3x3", 500, false);
    ASSERT_EQ(m_simpleListModel->m_expressionList.count(), 500);
    DSettingsAlt::deleteInstance();
}

TEST_F(Ut_SimpleListModel, updataList2)
{
    for (int i = 0; i < 500; i++) {
        m_simpleListModel->m_expressionList.append("1");
        m_simpleListModel->m_answerlist.append(Quantity(1));
    }
    m_simpleListModel->updataList(Quantity(9), "3x3", 500);
    ASSERT_EQ(m_simpleListModel->m_expressionList.count(), 500);
    DSettingsAlt::deleteInstance();
}

TEST_F(Ut_SimpleListModel, deleteItem)
{
    m_simpleListModel->m_expressionList.append("1");
    m_simpleListModel->m_answerlist.append(Quantity(1));
    m_simpleListModel->deleteItem(0);
    ASSERT_EQ(m_simpleListModel->m_expressionList.count(), 0);
    DSettingsAlt::deleteInstance();
}

TEST_F(Ut_SimpleListModel, copyToClipboard)
{
    m_simpleListModel->m_expressionList.append("1");
    m_simpleListModel->copyToClipboard(0);
    //无ASSERT
    DSettingsAlt::deleteInstance();
}

TEST_F(Ut_SimpleListModel, getAnswer)
{
    m_simpleListModel->m_answerlist.append(Quantity(1));
    m_simpleListModel->getAnswer(1);
    ASSERT_EQ(m_simpleListModel->getAnswer(0), Quantity(1));
    DSettingsAlt::deleteInstance();
}

TEST_F(Ut_SimpleListModel, radixChanged)
{
    m_simpleListModel->m_expressionList.append("123＋321 ＝ 444");
    m_simpleListModel->radixChanged(16, 10);
    m_simpleListModel->radixChanged(10, 8);
    m_simpleListModel->radixChanged(8, 2);
    m_simpleListModel->radixChanged(2, 16);
    DSettingsAlt::deleteInstance();
}

TEST_F(Ut_SimpleListModel, radixChanged1)
{
    m_simpleListModel->m_expressionList.append("－123and321 ＝ 444");
    m_simpleListModel->radixChanged(10, 2);
    DSettingsAlt::deleteInstance();
}

TEST_F(Ut_SimpleListModel, formatExpression)
{
    m_simpleListModel->formatExpression(10, "321");
    m_simpleListModel->formatExpression(8, "321");
    m_simpleListModel->formatExpression(2, "321");
    QString str = m_simpleListModel->formatExpression(16, "321");
    ASSERT_EQ(str, "0x321");
    DSettingsAlt::deleteInstance();
}

TEST_F(Ut_SimpleListModel, answerOutOfRange)
{
    m_simpleListModel->m_expressionList.append("123＋321 ＝ 444");
    m_simpleListModel->answerOutOfRange(Quantity(123));
    ASSERT_EQ(m_simpleListModel->m_expressionList.at(0), "123＋321 ＝123");
    DSettingsAlt::deleteInstance();
}
