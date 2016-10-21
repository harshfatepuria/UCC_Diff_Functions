subreddits = list()
user = r.get_redditor(user)
comments = user.get_comments(limit = None)
for comment in comments:
try:
json_comment = vars(comment)
subreddit_commented_on = json_comment['subreddit']
json_subreddit = vars(subreddit_commented_on)
subreddit_name = str(json_subreddit['display_name'])
subreddits.append(subreddit_name)
except:
continue
unique_subreddits = list(set(subreddits))
return unique_subreddits