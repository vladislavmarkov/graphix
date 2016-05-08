
class caption_width_height_test_: public ::testing::Test{
public:
    std::shared_ptr<gfx::window> window_;

protected:
    virtual void SetUp(){
        window_ = gfx::window::create("test", 100, 100);
    }
};

TEST_F(caption_width_height_test_, caption_width_height_test){
    EXPECT_EQ("test", window_->get_caption());
    EXPECT_EQ(100, window_->get_width());
    EXPECT_EQ(100, window_->get_height());
}

class empty_caption_test_: public ::testing::Test{
public:
    std::shared_ptr<gfx::window> window_;

protected:
    virtual void SetUp(){
        window_ = gfx::window::create("", 100, 100);
    }
};

TEST(window, empty_caption_test){
    try{
        std::shared_ptr<gfx::window> window_ = gfx::window::create("");
        FAIL() << "expected std::invalid_argument";
    }catch(std::invalid_argument e){
        EXPECT_STREQ("empty caption", e.what());
    }catch(...){
        FAIL() << "expected std::invalid_argument";
    }
}

TEST(window, caption_only_test){
    try{
        std::shared_ptr<gfx::window> window_ =
            gfx::window::create("caption only");
    }catch(...){
        FAIL() << "expected no exceptions";
    }
}
