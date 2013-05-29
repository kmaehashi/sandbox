#!/usr/bin/env python

# -*- coding: utf-8 -*-

import urllib2
import json

# configuration
owner = 'jubatus'
repo = 'jubatus'
state = 'open' # or 'closed'



def fetch(page):
    # fetch from API (no authentication required for public repos)
    url = 'https://api.github.com/repos/%s/%s/issues?state=%s&page=%d' % (owner, repo, state, page)
    response = urllib2.urlopen(url)

    # parse and print as CSV
    return json.loads(response.read())

def do_print(issues):
    for i in issues:
        issue_id = str(i['number'])
        milestone = i['milestone']
        if milestone:
            milestone_title = milestone['title']
        else:
            milestone_title = ''
        created_user = i['user']['login']
        title = i['title']
        labels = i.get('labels', None)
        if labels:
            labels_list = '|'.join(map(lambda x: x['name'], labels))
        else:
            labels_list = ''
        print '"%s","%s","%s","%s","%s"' % (issue_id, title, created_user, labels_list, milestone_title)

for i in range(1,10):
    issues = fetch(i)
    if len(issues) == 0:
        break
    do_print(issues)

