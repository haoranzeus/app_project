#!/usr/bin/python
import sys
import os

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
# return: a string of cpp code func.
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

# Translate a list of html_element to html module form
# parameters:
# func_list - the list of [func name, description, {parameters}]
# return: a html element
def formate_html_module(func_list):
	html = "\t\t<h1>" + func_list[0] + "</h1>\n"
	html += "\t\t<h2>description:</h2>\n"
	html += "\t\t<p>\n"
	html += "\t\t\t" + func_list[1] + "\n"
	html += "\t\t</p>\n"
	if len(func_list) == 3:
		html += "\t\t<h2>parameters:</h2>\n"
		html += "\t\t<p>\n"
		html += "\t\t\t" + func_list[2].replace('\n', '<br />\n\t\t\t') + "\n"
		html += "\t\t</p>\n"
	html += "\t\t<hr />\n"
	return html

# formate and write html_element to a html file
# parameters:
# html_element - html element string
# html_file - destination html file to write into
def func_element_html_formate(html_element, html_file):
	# html head
	html_head = "<!DOCTYPE html>\n<html>\n\t<head>\n"
	html_head += '\t\t<link rel="stylesheet" type="text/css" href="css/interface.css" />\n'
	html_head += "\t\t<title>test</title>\n\t<head>\n\n\t<body>\n"

	# html tail
	html_tail = "\t</body>\n</html>\n"

	html_list = get_func_dscp_para(html_element)
	if html_list == -1:
		return -1
	func_html = formate_html_module(html_list)
	func_html += "\n"
	file_size = os.stat(html_file).st_size	# get size of html_file
	fd = open(html_file, "rw+")
	if file_size == 0:		# if html file is empty, write html head
		fd.write(html_head)
	else:
		fd.seek(-len(html_tail), 2)
	fd.write(func_html)
	fd.write(html_tail)
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
#traversal_func_elements("demand.conf", func_element_html_formate, "my.html")
traversal_func_elements(sys.argv[1], func_element_cpp_formate, sys.argv[2])
traversal_func_elements(sys.argv[1], func_element_html_formate, sys.argv[3])
