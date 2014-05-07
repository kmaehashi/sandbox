#!/usr/bin/env python
# -*- coding: utf-8 -*-

from base64 import b64encode
import sys
import urllib2
import json

ORG_NAME = 'jubatus'

# Note:
# * Unauthenticated access is possible, but easily hit the API quota.
# * We don't support account with 2-factor auth enabled.
GH_USER = 'kmaehashi'
GH_PASS = 'foobar'

def debug(msg):
    sys.stderr.write(msg + "\n")

def get_url(url):
    debug(url)
    f = None
    cont = None
    try:
        r = urllib2.Request(url)
        # TODO replace it with standard urllib2 way
        r.add_header('Authorization', 'Basic ' + b64encode(GH_USER + ':' + GH_PASS))
        f = urllib2.urlopen(r)
        cont = f.read()
    finally:
        # TODO handle errors
        pass
    return cont

def get_repos(org):
    url = 'https://api.github.com/orgs/%s/repos' % org
    return json.loads(get_url(url))

def fetch(owner, repo, state, page):
    url = 'https://api.github.com/repos/%s/%s/issues?state=%s&page=%d' % (owner, repo, state, page)
    return json.loads(get_url(url))

def do_print(repo, issues):
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
        # TODO more info
        # TODO replace with standard csv module
        print '"%s","%s","%s","%s","%s","%s"' % (repo,issue_id, title, created_user, labels_list, milestone_title)

def fetch_issues_for(repo):
    issues = []
    page = 0
    while(True):
        page += 1
        issues_in_page = fetch(ORG_NAME, repo, 'open', page)
        if len(issues_in_page) == 0:
            break
        issues += issues_in_page
        debug("fetch page %d of repo %s" % (page, repo))
    return issues

def main():
    repos = map(lambda r: r['name'], filter(lambda r: r['has_issues'], get_repos(ORG_NAME)))
    debug('got repos: ' + str(repos))
    for repo in repos:
        issues = fetch_issues_for(repo)
        do_print(repo, issues)

if __name__ == '__main__':
    main()
