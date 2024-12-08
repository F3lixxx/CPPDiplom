#pragma once 
#include <iostream>
#include <pqxx/pqxx>
#include <map>
#include <set>

class data_base{
private:
    const std::string connection_name;
    pqxx::connection* connection_ptr = NULL;
    std::string last_error;
    bool connect_db();
    bool create_table();

public:
    explicit data_base(const std::string& params) noexcept;

    bool start_db();
    std::string view_last_error();
    void show_last_error();

    data_base(const data_base& other) = delete;
    data_base(data_base&& other) noexcept;
    data_base& operator=(const data_base& other) = delete;
    data_base& operator=(data_base&& other) noexcept;
    ~data_base();

    std::map<std::string, int> url_list_words(const std::set<std::string>& word_set);
    int count_words_url(const std::set<std::string>& word_set, std::string url);
    std::multimap<std::string, int> get_word_url_tables(const std::set<std::string>& wordsA_set);
    std::string where_or_expected(const std::set<std::string>& word_set, pqxx::work& tx);
};