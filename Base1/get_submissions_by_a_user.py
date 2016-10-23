user = r.get_redditor(user)
submissions = user.get_submitted(limit=None)
print "# submissions by",user,"=",
len_submissions = 0
for submission in submissions:
len_submissions = len_submissions + 1
print len_submissions