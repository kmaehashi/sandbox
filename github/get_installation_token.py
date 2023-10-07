import sys
from github import Github
from github import Auth


app = Auth.AppAuth(app_id=sys.argv[1], private_key=open(sys.argv[2]).read())
z = Github(auth=Auth.AppInstallationAuth(app_auth=app, installation_id=int(sys.argv[3])))
print(z.get_repo('cupy/cupy'))
