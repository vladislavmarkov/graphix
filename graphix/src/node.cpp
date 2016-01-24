#include <algorithm>
#include <gfx/node.hpp>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>

using std::begin; using std::end;
using std::for_each;
using std::invalid_argument;
using std::shared_ptr;
using std::stack;
using std::string;

namespace gfx{

shared_ptr<node> find_node(shared_ptr<node> root, const string &name){
    if (!root){
        throw invalid_argument("root is null pointer");
    }

    if (name.empty()){
        return shared_ptr<node>();
    }

    std::stack<shared_ptr<node>> nodes;
    nodes.push(root);
    while (!nodes.empty()){
        auto current = nodes.top();
        nodes.pop();
        if (current && current->name_ == name){
            return current;
        }

        for_each(begin(current->children_), end(current->children_),
            [&nodes](shared_ptr<node> &n){
                if (n) nodes.push(n);
            }
        );
    }

    return shared_ptr<node>();
}

}
