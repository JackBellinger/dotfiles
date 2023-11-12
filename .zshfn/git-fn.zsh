#!/usr/bin/env zsh

alias gs="gst"

function git_current_branch() {
   ref=$(git symbolic-ref HEAD 2> /dev/null) || \
   ref=$(git rev-parse --short HEAD 2> /dev/null) || return
   echo ${ref#refs/heads/}
}

function gcpm() {
   #cf && ccl && ct
   #git commit(a) and push w/ message (add an arg to disable precommit hooks)
   if [ -z "$2" ]; then
       git commit -am "$1"
   else
       git commit -anm "$1"
   fi
   git push --set-upstream origin $(git_current_branch) #set upstream in case the branch is new
}

function gcjb() {
   git clone git@github.com:jackbellinger/$1
}

function gda() {
    #checks the diff of ever git repo in ~/code and prints the status for any that have changes
    curdir=$(pwd)
    for d in ~/code/* ; do
         if [ -d $d ] ; then
             cd $d
             if [ -d "./.git" ] ; then
                if ! git diff-index --quiet HEAD --; then #if there are changes
                    echo "\n\n${Brown_Orange}diffing $d${End_Color}"
                    git status --porcelain
                fi
            fi
        fi
    done
    cd $curdir
}

function gpa() {
    #Crawls ~/code directory, updating branches and pulling updates for all git repos
    curdir=$(pwd)
    for d in ~/code/* ; do
        if [ -d $d ] ; then
            cd $d
            if [ -d "./.git" ] ; then
                echo "\n\n ${Red}updating $d${End_Color}"
                git remote -v update --prune
                gfab
            fi
        fi
    done
    cd $curdir
}

function gfab() {
    #git fetch all branches
    currbranch=$(git rev-parse --abbrev-ref HEAD)
    git branch -r | grep -v '\->' | while read remote; do
        branch_name="${remote#origin/}"
        if [[ -n "$(git branch --list ${branch})" ]]; then #if the branch dne on local
            git branch --track "$branch_name" "$remote";
        fi
        UPSTREAM=${1:-'@{u}'}
        LOCAL=$(git rev-parse @)
        REMOTE=$(git rev-parse "$UPSTREAM")
        BASE=$(git merge-base @ "$UPSTREAM")

        if [ $LOCAL = $REMOTE ]; then
            echo "Up-to-date"
        elif [ $LOCAL = $BASE ]; then
            echo "Need to pull"
            git pull
        elif [ $REMOTE = $BASE ]; then
            echo "Need to push"
            read -p "Git pull?" yn
            case $yn in
                [Yy]* ) git pull; break;;
                [Nn]* ) exit;;
                * ) echo "Please answer yes or no.";;
            esac
        else
            echo "Diverged"
        fi
        if git diff-index --quiet HEAD --; then #if there are no local changes to the current branch
            git checkout "${remote#origin/}";
            git pull --ff-only ;
        else
            echo "$currbranch has changes, please commit before I can pull $branch_name"
        fi
    done
    git checkout $currbranch
}