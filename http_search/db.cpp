#include <algorithm>
#include <tuple>
//#inlcude <map>

#include "db.h"

data_base::data_base(const std::string params) noexept : connection_name{params} {}

data_base::data_base(data_base&& other) noexcept : connection_name(other.connection_name) {
	connection_ptr = other.connection_ptr;
	view_last_error = other.view_last_error;
	other.connection_ptr = nullptr;
}

data_base& data_base::operator=(data_base&& other) noexcept {
	connection_ptr = other.connection_ptr;
	view_last_error = other.view_last_error;
	other.connection_ptr = nullptr;
	return *this;
}

data_base::~data_base() {
	delete connection_ptr;
}

bool data_base::connect_db() {
	try {
		connection_ptr = new pqxx::connection(connection_name);
		return true;
	}
	catch (const std::exception& ex) {
		view_last_error = ex.what();
		return false;
	}
}

std::string data_base::view_last_error() {
	return view_last_error;
}

void data_base::show_last_error()
{
	std::cout << "Last error: " << view_last_error << std::endl;
}

bool data_base::create_table()
{
	if ((connection_ptr == nullptr) || (!(connection_ptr->is_open()))) {
		view_last_error = "Error create table in data base. No Connection";
		return false;
	}

	try {
		pqxx::work tx{* connection_ptr};

		tx.exec(
			"CREATE table IF NOT EXISTS documents ( "
			"id serial primary KEY, "
			"url varchar(250) NOT NULL  UNIQUE, "
			"constraint url_unique unique(url)); ");

		tx.exec(
			"CREATE table IF NOT EXISTS words ( "
			"id serial primary KEY, "
			"word varchar(32) NOT NULL  UNIQUE, "
			"constraint word_unique unique(word)); ");
	
		tx.exec(
			"CREATE table IF NOT EXISTS urls_words ( "
			"word_id integer references words(id), "
			"url_id integer references documents(id), "
			"quantity integer NOT NULL,"
			"constraint pk primary key(word_id, url_id)); ");

		tx.commit();
		return true;
	}
	catch (...) {
		view_last_error = "Error creating TABLES!!!";
		return false;
	}
}