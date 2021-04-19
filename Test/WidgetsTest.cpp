//
// Created by Niccolo on 01/04/2021.
//

#include "gtest/gtest.h"
#include "Game.h"
#include "Mock/MockGameConfig.h"
#include "Widgets/Widget.h"
#include "Widgets/TextWidget.h"
#include "Widgets/ImageWidget.h"
#include "Widgets/ShapeWidget.h"

class TestSubject : public Subject{
public:
    Observer * m_observer;
    std::string m_item_name;

    void subscribe(Observer *observer, const std::string &item_name) override{
        m_observer = observer;
        m_item_name = item_name;
    }

    void unsubscribe(Observer *observer, const std::string &item_name) override{
        if(m_observer == observer)
            m_observer = nullptr;
        if(m_item_name == item_name)
            m_item_name = "";
    }

    void notify(const std::string &item_value) override{
        m_observer->data_update(m_item_name, item_value);
    }

};

class TestWidget : public Widget {
private:
    sf::Vector2f m_parent_position;
    std::string m_item_name;
    std::string m_item_value;
public:
    explicit TestWidget(std::string name) : Widget(std::move(name)){}
    sf::Vector2f getOffset() { return m_parent_position; }
    std::string getItemName() { return m_item_name; }
    std::string getItemValue() { return m_item_value; }
    void _render(sf::RenderWindow &window, const sf::Vector2f &parent_position) override {
        m_parent_position = parent_position;
    }

    void data_update(const std::string &item_name, const std::string &item_value) override {
        m_item_name = item_name;
        m_item_value = item_value;
    }
};

class WidgetsTest : public ::testing::Test{
public:
    sf::RenderWindow window;

    WidgetsTest() {
        Game::deleteInstance();
        auto state = new GameStateMachine(State::Init);
        auto cfg   = new MockGameConfig();
        auto resm  = new ResourceManager();
        auto fact  = new Factory();
        auto scn   = new SceneManager();
        auto stats = new GameStats();
        auto score = new ScoreManager();
        Game* game = Game::instance(state, cfg, resm, fact, scn, stats, score);
        dynamic_cast<MockGameConfig*>(CONFIG)->setTextureResource("Texture", "Texture.png");
    }
};

TEST_F(WidgetsTest, EmptyWidget){
    auto widget = std::unique_ptr<Widget>(new Widget("WIDGET"));
    ASSERT_EQ(widget->findObjectByName("WIDGET"), widget.get());
}

TEST_F(WidgetsTest, AddWidget){
    auto widget = std::unique_ptr<Widget>(new Widget("WIDGET"));
    auto child_widget = new Widget("CHILD_WIDGET");
    widget->add(child_widget);
    ASSERT_EQ(widget->findObjectByName("CHILD_WIDGET"), child_widget);
}

TEST_F(WidgetsTest, WidgetPosition){
    auto widget = std::unique_ptr<TestWidget>(new TestWidget("WIDGET"));
    widget->setPosition(sf::Vector2f(10,10));
    auto widget_2 = new TestWidget("WIDGET_2");
    widget->add(widget_2);
    widget_2->setPosition(sf::Vector2f(10,10));
    widget_2->render(window);
    auto widget_3 = new TestWidget("WIDGET_3");
    widget_2->add(widget_3);
    widget_3->setPosition(sf::Vector2f(10,10));
    widget->render(window);
    ASSERT_EQ(widget->getOffset(), sf::Vector2f(10,10));
    ASSERT_EQ(widget_2->getOffset(), sf::Vector2f(20,20));
    ASSERT_EQ(widget_3->getOffset(), sf::Vector2f(30,30));
}

TEST_F(WidgetsTest, TestObserver){
    auto widget = std::unique_ptr<TestWidget>(new TestWidget("WIDGET"));
    auto subject = std::unique_ptr<TestSubject>(new TestSubject);
    auto subject2 = std::unique_ptr<TestSubject>(new TestSubject);
    widget->observe(subject.get(), "WIDGET_ITEM");
    ASSERT_EQ(subject->m_item_name, "WIDGET_ITEM");
    ASSERT_EQ(subject->m_observer, widget.get());
    subject->notify("WIDGET_VALUE");
    ASSERT_EQ(widget->getItemName(), "WIDGET_ITEM");
    ASSERT_EQ(widget->getItemValue(), "WIDGET_VALUE");
    widget->observe(subject2.get(), "WIDGET_ITEM");
    ASSERT_EQ(subject->m_item_name, "");
    ASSERT_EQ(subject->m_observer, nullptr);
}

TEST_F(WidgetsTest, SetString){
    auto text_widget = std::unique_ptr<TextWidget>(new TextWidget("WIDGET"));
    text_widget->setFont("RETRO_GAMING_FONT");
    text_widget->setString("");
    ASSERT_EQ(text_widget->getString(), "");
    ASSERT_EQ(text_widget->getSize(), sf::Vector2f(0,0));
    text_widget->setString("TestString");
    ASSERT_EQ(text_widget->getString(), "TestString");
    sf::Vector2f size = text_widget->getSize();
    ASSERT_NE(size, sf::Vector2f(0,0));
    text_widget->setString("LongTestString");
    ASSERT_EQ(text_widget->getString(), "LongTestString");
    sf::Vector2f size2 = text_widget->getSize();
    ASSERT_EQ(size2.y, size.y);
    ASSERT_GT(size2.x, size.x);
}

TEST_F(WidgetsTest, SetStringTimer){
    auto text_widget = std::unique_ptr<TextWidget>(new TextWidget("WIDGET"));
    text_widget->setString("Test string");
    text_widget->startTimer(sf::seconds(1));
    ASSERT_EQ(text_widget->isVisible(text_widget.get()), true);
    sf::sleep(sf::seconds(1));
    text_widget->update(1000);
    ASSERT_EQ(text_widget->isVisible(text_widget.get()), false);
    ASSERT_EQ(text_widget->getString(), "");
}

TEST_F(WidgetsTest, SetImage){
    auto image_widget = std::unique_ptr<ImageWidget>(new ImageWidget("WIDGET"));
    image_widget->setPosition(sf::Vector2f(0,0));
    image_widget->setTexture("Texture");
    image_widget->update(1000);
    ASSERT_EQ(image_widget->getSize(), sf::Vector2f(100,100));
    image_widget->setTexture("Texture", {300, 300});
    image_widget->update(1000);
    ASSERT_EQ(image_widget->getSize(), sf::Vector2f(300,300));
}

TEST_F(WidgetsTest, SetShape){
    auto shape_widget = std::unique_ptr<ShapeWidget>(new ShapeWidget("WIDGET"));
    shape_widget->setSize(sf::Vector2f(10,10));
    shape_widget->update(1000);
    ASSERT_EQ(shape_widget->getSize(), sf::Vector2f(10,10));
}