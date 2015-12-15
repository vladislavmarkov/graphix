#include <gfx/application.h>
#include <future>
#include <iostream>

TEST(application, running_closing_by_different_threads){
    try{
        std::unique_ptr<gfx::window> window_ =
            gfx::window::create("window");

        std::promise<int> run_promise;
        std::future<int> run_future = run_promise.get_future();
        std::thread([](std::promise<int> &p, gfx::window &w){
            p.set_value(gfx::run(w));
        }, std::ref(run_promise), std::ref(*window_)).detach();

        window_->close();
        EXPECT_EQ(0, run_future.get());
    }catch(...){
        FAIL() << "expected no exceptions";
    }
}
