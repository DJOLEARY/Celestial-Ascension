# Project 3
#### Created by Darren & D.J


SFML is included in the repo for now. This is subject to change based on the requirements. Compiles on release and debug for x86.

## Suggested git Workflow 
1. Clone the remote repository (once-off operation).
2. Create your a branch for the feature you are working on: `git checkout -b feature-name`
3. Add/stage your files: `git add .`
4. Commit your changes: `git commit -m 'Add some feature'`
5. Submit a pull request to fetch the latest version of the remote master: `git pull origin master --rebase`

    This command undoes your commits, applies the commits in the master branch to your feature branch, then applies your commits back to the feature branch.
6. Resolve any merge conflicts.
7. Push to your remote feature branch: `git push origin feature-name`
8. When your feature is complete, merge it with the master branch in three steps:

8.1 Switch to master branch: `git checkout master` 
8.2 Merge the feature branch with the master branch: `git merge feature-name`
8.3 Push to the remote master branch: `git push origin master`