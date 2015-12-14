
class window_caption_width_height_test: public ::testing::Test{
public:
    std::unique_ptr<gfx::window> window_;

protected:
    virtual void SetUp(){
        window_ = gfx::window::create("test", 100, 100);
    }
};

TEST_F(window_caption_width_height_test, caption_width_height_test){
    EXPECT_EQ("test", window_->get_caption());
    EXPECT_EQ(100, window_->get_width());
    EXPECT_EQ(100, window_->get_height());
}
