#include "HelloWorldScene.h"
#include <iostream>
using namespace std;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    auto array=__Array::create();
    auto str1=__String ::create("str1");
    auto str2=__String::create("str2");
    auto str3=__String::create("str3");
    auto str4=__String::create("str4");
    array->addObject(str1);
    array->addObject(str2);
    array->addObject(str3);
    array->addObject(str4);
    for (int i=0; i<array->count(); i++) {
        auto tmp=(__String*)array->objectAtIndex(i);
        log("str=%s",tmp->getCString());
        log("str=%s",tmp->_string.c_str());
    }
    array->removeLastObject();
    
    auto dic=__Dictionary::create();
    dic->setObject(str1, "NAmE");
    dic->objectForKey("NAmE");
    testVector();
    testMap();
    testValue();
    
    return true;
}
void HelloWorld::testVector()
{
    std::vector<int >aa;
    //std::vector<int>::iterator itor=aa.begin();
    for (int n=1; n<55; n++) {
        aa.push_back(n);
    }
    for (int i=1; i<201; i++) { //洗牌
        int tmp=arc4random()%54;
        
            //aa.insert(itor, tmp);
            
            std::swap(aa.at(0), aa.at(tmp));
        
            
        
    }
    for(auto sp:aa){  // 快速遍历
        log("%d",sp);
    }
    
    
    auto spri01=Sprite::create();
    spri01->setTag(1);
    
    Vector<Sprite*>vec00;
    vec00.pushBack(spri01); //00----1
    auto spri02=Sprite::create();
    Vector<Sprite*>vec11(5);
    vec11.insert(0, spri02);  //11----1,2
    vec11.pushBack(vec00);  //可以加入整个Vector
    for(auto sp:vec11)
    {
        log(" the tag==%d",sp->getTag());
    }
    Vector<Sprite*>vec22(vec00); //22----1
    if (vec00.equals(vec22)) {
        log("00  is equal to 22");
    }
    if (!vec11.empty()) {
        if (vec11.capacity()==vec11.size()) {
            log("capacity  ==  size");
        }else{
            vec11.shrinkToFit(); //收缩vector，以便内存对应上元素个数
            log("11: capacity=%zd, size=%zd",vec11.capacity(),vec11.size());
        }
        vec11.swap(vec11.front(), vec11.back());//交换位置
        if (vec22.contains(spri01)) {
            log("the index of spri01 in vec22 is :  %zd",vec22.getIndex(spri01));
        }
        vec11.erase(vec11.find(spri01));  //find()函数返回一个迭代器
        //vec11.eraseObject(spri01,true);
        //vec11.erase(1);
        //vec11.popBack();
        vec11.clear();
        log("the size of vec11 is: %zd",vec11.size());
    }
}

void HelloWorld::testMap() //插入和获取，first，second，（key,）
{
    //map_insert(&map,key,value);
    //value,==Integer,Float,..
    //value.asInt,asBool,asByte,..,val.getDescription();
    auto spr0=Sprite::create();
    spr0->setTag(0);
    Map<std::string, Sprite*>map0;
    std::string mapKey0="MAP_KEY0";
    map0.insert(mapKey0, spr0);  //map 通过插入的形式给map添加元素
    log("the size of map is:%zd",map0.size());
    Map<std::string, Sprite*>map1(map0);   //调用拷贝构造
    std::string mapKey1="MAP_KEY1";
    if (!map1.empty()) {
        auto tempSp=(Sprite*)map1.at(mapKey0);
        log("sprite tag=%d",tempSp->getTag());
        auto spr1=Sprite::create();
        spr1->setTag(1);
        map1.insert(mapKey1, spr1);
        
        std::vector<std::string>mapKeyVec; //声明一个为字符串类型的向量数组来接收keys
        mapKeyVec=map1.keys();
        for(auto key:mapKeyVec){
            auto spTag=map1.at(key)->getTag();  //用at()方法，有越界的判断
            log("the sprite tag=%d , Map key=%s",spTag,key.c_str());
            log("Element with key :%s : is located in blucket .T%zd",key.c_str(),map1.bucket(key));
            
        }
        log("%zd  buckets in the Map container",map1.bucketCount());
        log("%zd element in bucket 1",map1.bucketSize(1));
        //如果map 不为空的话，从中获取一个随机对象，否则返回一个空指针
        log("the random object tag =%d",map1.getRandomObject()->getTag());
        //find（key）可以用来在容器中根据key 找到一个元素
        //erase可以用来指定迭代器删除一个元素
        log("before remove sp0,size of map is %zd",map1.size());
        map1.erase(map1.find(mapKey0));
        log("After remove spr0 ,the size of map is :%zd",map1.size());
    }
    
}

void HelloWorld::pairTest()
{
    //功能：pair 将一对值组合成一个值，这一对值可以有不同的数据类型（T1和T2），两个值可以用pair得两个公有成员first和second 访问
    std::pair<int ,double>p1;
    std::pair<int ,double>p2(1,2.4);
    std::pair<int , double>p3(p2);  //使用拷贝构造
    
    std::pair<int , double>p4; //使用默认构造
    p4.first=1;
    p4.second=2.5;
    cout<<p4.first<<"   ,  "<<p4.second<<endl;
    pair<int , double>p6;
    p6=make_pair(1, 1.2);
    
    
}

 void HelloWorld::testValue()
{
    Value val;
    if (val.isNull()) {
        log("the val is null...");
    }
    else{
        std::string str=val.getDescription();
        log("the description of val is :%s",str.c_str());
        log("");
        
    }
    Value val1(65);
    log("the despcription of val1 is: %s",val1.getDescription().c_str());
    log("the Byte of val1:  %c",val1.asByte());
    
    std::string strv="string";
    Value val2(strv);
    log("the val2 des  ：%s",val2.getDescription().c_str());
    
    auto spr=Sprite::create();
    Vector<Ref*>* vecV=new Vector<Ref*>();
    vecV->pushBack(spr);
    
    Value val3(vecV);
    log("the desP  od the vector vaue :%s",val3.getDescription().c_str());
    
    Map<string, Ref*>* mapV=new Map<string, Ref*>();
    mapV->insert(strv, spr);
    Value val4(mapV);
    log("val4  :%s",val4.getDescription().c_str());
    delete mapV;
    
    Value val6(&val4);
    log("val6  :%s",val6.getDescription().c_str());
    
    val2=val1;
    log(" val2  :%s",val2.getDescription().c_str());
    val2=4;
    log("change val2===%s",val2.getDescription().c_str());
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
