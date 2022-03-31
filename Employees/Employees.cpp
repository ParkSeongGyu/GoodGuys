﻿#include "Employees.h"

#include <algorithm>
#include <exception>
#include <unordered_map>

using namespace std;

CL strToCL(const std::string& cl_str)
{
	if (cl_str == "CL1")
		return CL::CL1;
	else if (cl_str == "CL2")
		return CL::CL2;
	else if (cl_str == "CL3")
		return CL::CL3;
	else if (cl_str == "CL4")
		return CL::CL4;

	throw invalid_argument("정해지지 않은 CL 형식");
}

CERTI strToCerti(const std::string& certi_str)
{
	if (certi_str == "ADV")
		return CERTI::ADV;
	else if (certi_str == "PRO")
		return CERTI::PRO;
	else if (certi_str == "EX")
		return CERTI::EX;

	throw invalid_argument("정해지지 않은 CERTI 형식");
}

unsigned strToEmployeeNumber(const std::string& num)
{
	string t = "";

	if ('6' <= num[0] && num[0] <= '9')
		t = "19";
	else
		t = "20";

	t.append(num);

	return stoi(t);
}

class EmployeesImpl : public Employees
{
public:
	virtual void add(Employee& new_employee) override
	{
		employeeList::const_iterator pos = findAscendingOrderPositionAtList(new_employee);
		map.insert(std::pair<unsigned, Employee*>(new_employee.employeeNumber, &(*list.emplace(pos, new_employee))));
	}

	virtual void del(Employee& del_employee) override
	{
		try {
			list.remove(*findEmployeePointerFromMap(del_employee));
			map.erase(del_employee.employeeNumber);
		}
		catch (invalid_argument& e) {
			cout << e.what();
			throw e;
		}
	}

	virtual void modify(Employee& target, std::function<void(Employee&)> func) override
	{
		try {
			Employee& t = *findEmployeePointerFromMap(target);
			func(t);
		}
		catch (invalid_argument& e) {
			cout << e.what();
			throw e;
		}
		catch (exception& e) {
			throw e;
		}
	}

	virtual const employeeList* const getEmployees() const override
	{
		return &list;
	}

private:
	employeeList list;
	unordered_map<unsigned, Employee*> map;

	Employee* findEmployeePointerFromMap(Employee& target)
	{
		auto search = map.find(target.employeeNumber);
		if (search == map.end())
			throw invalid_argument("존재하지 않는 직원");
		return map.find(target.employeeNumber)->second;
	}

	employeeList::const_iterator findAscendingOrderPositionAtList(Employee& empl)
	{
		return find_if(list.begin(), list.end(), [empl](Employee& listEmpl)->bool { return empl < listEmpl; });
	}
};

Employees* createEmployees()
{
	return new EmployeesImpl();
}
