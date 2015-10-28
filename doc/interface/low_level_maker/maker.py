#!/usr/bin/python
import sys

# Get a list [func name, descripiton, parameters] from a func_element string
def get_func_dscp_para(func_element):
	func_num = func_element.find('funcname:\n')
	dscp_num = func_element.find('description:\n')
	para_num = func_element.find('parameters:\n')
	if func_num == -1:
		#print('funcname not found')
		return -1
	if dscp_num == -1:
		#print('description not found')
		return -1
	func = func_element[func_num + len('funcname:\n'):dscp_num]
	if para_num == -1:
		dscp = func_element[dscp_num + len('description:\n'):]
	else:
		dscp = func_element[dscp_num + len('description:\n'):para_num]
	if func[-1] == '\n':
		func = func[:-1]
	if dscp[-1] =='\n':
		dscp = dscp[:-1]
	if para_num != -1:
		para = func_element[para_num + len('parameters:\n'):]
		ret = [func, dscp, para]
	else:
		ret = [func, dscp]
	return ret

# Translate a list of func_element to code module form
# parameters:
# func_list - the list of [func name, description, {parameters}]
def formate_code_module(func_list):
	# create annotation
	code = "// func name:\t" + func_list[0] + "\n"
	code += "// description:\t" + func_list[1] + "\n"
	if len(func_list) == 3:
		paras = func_list[2].split("\n")
		code += "// parameters:\t"
		for para in paras:
			code += para + "\n//\t\t"
		code = code[:-4]	# delete redundant "//\t\t"

	# create function code
	code += func_list[0] + "{\n"
	code += "\n}\n"

	return code

# fomate func_element to cpp code, and write to cpp_file
# parameters:
# func_element - func_element string
# cpp_file - destination cpp file to write into
def func_element_cpp_formate(func_element, cpp_file):
	func_list = get_func_dscp_para(func_element)
	if func_list == -1:
		return -1
	func_code = formate_code_module(func_list)
	func_code += "\n"
	fd = open(cpp_file, "a")
	fd.write(func_code)
	fd.close
	
# traversal a configure file to get func elements.
# parameters:
# conf_file - a configure file.
# element_hand_func - a function handle the func_element.
# dest_file - a file. it is the parameter of element_hand_func. we write the result to this file
def traversal_func_elements(conf_file, element_hand_func, dest_file):
	f_dest = open(dest_file, "w")
	f_dest.truncate()
	f_dest.close()
	fd = open(conf_file, "r")
	element = ""
	func_code = ""
	for line in fd:
		if line.find("=======================") != -1:
			element_hand_func(element.strip(), dest_file)
			element = ''
		else:
			element += line
	fd.close()

# main body
#traversal_func_elements("demand.conf", func_element_cpp_formate, "test.cpp")
traversal_func_elements(sys.argv[1], func_element_cpp_formate, sys.argv[2])

