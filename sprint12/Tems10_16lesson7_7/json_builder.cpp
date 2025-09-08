class Builder {
public:
    Builder();
    
    DictKeyContext Key(const std::string&);
    Builder& Value(Node::Value);
    DictItemContext StartDict();
    ArrayItemContext StartArray();
    Builder& EndDict();
    Builder& EndArray();
    Node Build();

private:
    class BaseContext {
    public:
        BaseContext(Builder& builder) : builder_(builder) {}
        
        // Все методы Builder
        DictKeyContext Key(const std::string& key);
        BaseContext Value(Node::Value value);
        DictItemContext StartDict();
        ArrayItemContext StartArray();
        Builder& EndDict();
        Builder& EndArray();
        
    protected:
        Builder& builder_;
    };

    class DictItemContext : public BaseContext {
    public:
        using BaseContext::BaseContext;
        DictKeyContext Key(const std::string& key);
        Builder& EndDict();
        
        // Запрещаем недопустимые
        BaseContext Value(Node::Value) = delete;
        ArrayItemContext StartArray() = delete;
    };

    // ... аналогично для других контекстов
    
    // Данные Builder
    Node root_;
    std::vector<Node*> nodes_stack_;
    std::string current_key_;
    bool key_expected_ = false;
};
