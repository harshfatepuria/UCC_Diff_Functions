import statistics
import fnmatch
import math
import os
import pprint as pp
from sklearn import svm
from sklearn import metrics
from sklearn.preprocessing import MinMaxScaler


def get_fold(typeOfTest,test_start,test_end,validate_start,validate_end,train_start,train_end):
	input_file=open('dataset_shuffle.csv' , 'r')
	dataset=input_file.read().split("\n")

	if typeOfTest==1:
		# accoustic
		start_column=3
		end_column=5
	elif typeOfTest==0:
		# visual
		start_column=6
		end_column=8
	else:
		# multimodal
		start_column=3
		end_column=8

	test1_data=list()
	test1_label=list()
	validate1_data=list()
	validate1_label=list()
	train1_data=list()
	train1_label=list()


	for i in range(test_start,test_end+1):
		row=list()
		data=dataset[i].split(",")

		for j in range(start_column,end_column+1):
			row.append(float(data[j]))
		test1_data.append(row)
		test1_label.append(int(data[2]))



	for i in range(validate_start,validate_end+1):
		row=list()
		data=dataset[i].split(",")
		for j in range(start_column,end_column+1):
			row.append(float(data[j]))
		validate1_data.append(row)
		validate1_label.append(int(data[2]))



	for i in range(train_start,train_end+1):
		row=list()
		data=dataset[i].split(",")
		for j in range(start_column,end_column+1):
			row.append(float(data[j]))
		train1_data.append(row)
		train1_label.append(int(data[2]))
	return test1_data,test1_label,validate1_data,validate1_label,train1_data,train1_label


def perform_svm(typeOfTest,test_start,test_end,validate_start,validate_end,train_start,train_end):
	test1_data,test1_label,validate1_data,validate1_label,train1_data,train1_label = get_fold(typeOfTest,test_start,test_end,validate_start,validate_end,train_start,train_end)
	# train1_data=MinMaxScaler().fit_transform(train1_data)
	# validate1_data=MinMaxScaler().fit_transform(validate1_data)
	# test1_data=MinMaxScaler().fit_transform(test1_data)

	clf = svm.LinearSVC()
	
	accuracy=list()

	for c in [0.001,0.01,0.1,1,10,100]:
		validation_result=list()
		clf.set_params(C=c)
		clf.fit(train1_data, train1_label)
		correct_classification = 0
		i=0
		for line in validate1_data:
			validation_result.append(clf.predict([line])[0])
		accuracy.append(metrics.accuracy_score(validate1_label,validation_result))
	print "Accuracy in validation (max): ",max(accuracy) 
	print "Accuracy in validation (average): ",statistics.mean(accuracy) 
	

	cMax=math.pow(10,(accuracy.index(max(accuracy))-3))
	print "Hyperparameter(c) for max accuracy = ",cMax

	clf = svm.LinearSVC()
	train_results=list()
	clf.set_params(C=cMax)
	clf.fit(train1_data, train1_label)
	for line in train1_data:
		train_results.append(clf.predict([line])[0])
	print "Accuracy in training: ",metrics.accuracy_score(train1_label,train_results)

	clf = svm.LinearSVC()
	test_results=list()
	clf.set_params(C=cMax)
	clf.fit(train1_data, train1_label)
	print "\nTest Results:"
	for line in test1_data:
		predicted = clf.predict([line])[0]
		test_results.append(predicted)
		print predicted
	print "\nAccuracy in test: ",metrics.accuracy_score(test1_label,test_results)
