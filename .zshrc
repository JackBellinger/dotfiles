# If you come from bash you might have to change your $PATH.
# export PATH=$HOME/bin:/usr/local/bin:$PATH

# Path to your oh-my-zsh installation.
export ZSH="/home/jackson/.oh-my-zsh"

# Set name of the theme to load --- if set to "random", it will
# load a random theme each time oh-my-zsh is loaded, in which case,
# to know which specific one was loaded, run: echo $RANDOM_THEME
# See https://github.com/robbyrussell/oh-my-zsh/wiki/Themes
#ZSH_THEME="robbyrussell"
ZSH_THEME=powerlevel10k/powerlevel10k

# Set list of themes to pick from when loading at random
# Setting this variable when ZSH_THEME=random will cause zsh to load
# a theme from this variable instead of looking in ~/.oh-my-zsh/themes/
# If set to an empty array, this variable will have no effect.
# ZSH_THEME_RANDOM_CANDIDATES=( "robbyrussell" "agnoster" )

# Uncomment the following line to use case-sensitive completion.
# CASE_SENSITIVE="true"

# Uncomment the following line to use hyphen-insensitive completion.
# Case-sensitive completion must be off. _ and - will be interchangeable.
 HYPHEN_INSENSITIVE="true"

# Uncomment the following line to disable bi-weekly auto-update checks.
# DISABLE_AUTO_UPDATE="true"

# Uncomment the following line to automatically update without prompting.
 DISABLE_UPDATE_PROMPT="true"

# Uncomment the following line to change how often to auto-update (in days).
# export UPDATE_ZSH_DAYS=13

# Uncomment the following line if pasting URLs and other text is messed up.
# DISABLE_MAGIC_FUNCTIONS=true

# Uncomment the following line to disable colors in ls.
# DISABLE_LS_COLORS="true"

# Uncomment the following line to disable auto-setting terminal title.
# DISABLE_AUTO_TITLE="true"

# Uncomment the following line to enable command auto-correction.
# ENABLE_CORRECTION="true"

# Uncomment the following line to display red dots whilst waiting for completion.
 COMPLETION_WAITING_DOTS="true"

# Uncomment the following line if you want to disable marking untracked files
# under VCS as dirty. This makes repository status check for large repositories
# much, much faster.
# DISABLE_UNTRACKED_FILES_DIRTY="true"

# Uncomment the following line if you want to change the command execution time
# stamp shown in the history command output.
# You can set one of the optional three formats:
# "mm/dd/yyyy"|"dd.mm.yyyy"|"yyyy-mm-dd"
# or set a custom format using the strftime function format specifications,
# see 'man strftime' for details.
# HIST_STAMPS="mm/dd/yyyy"

# Would you like to use another custom folder than $ZSH/custom?
# ZSH_CUSTOM=/path/to/new-custom-folder

# Which plugins would you like to load?
# Standard plugins can be found in ~/.oh-my-zsh/plugins/*
# Custom plugins may be added to ~/.oh-my-zsh/custom/plugins/
# Example format: plugins=(rails git textmate ruby lighthouse)
# Add wisely, as too many plugins slow down shell startup.
plugins=(
git
tmux
)

source $ZSH/oh-my-zsh.sh
 
export PATH=$PATH:/home/jackson/lib/tau-2.28.2/x86_64/bin
export PATH=$PATH:/home/jackson/lib/pdtoolkit-3.25/x86_64/bin

# User configuration

# export MANPATH="/usr/local/man:$MANPATH"

# You may need to manually set your language environment
# export LANG=en_US.UTF-8

# Preferred editor for local and remote sessions
# if [[ -n $SSH_CONNECTION ]]; then
#   export EDITOR='vim'
# else
#   export EDITOR='mvim'
# fi

# Compilation flags
# export ARCHFLAGS="-arch x86_64"

# Set personal aliases, overriding those provided by oh-my-zsh libs,
# plugins, and themes. Aliases can be placed here, though oh-my-zsh
# users are encouraged to define aliases within the ZSH_CUSTOM folder.
# For a full list of active aliases, run `alias`.
#

Black='\033[0;30m'
 Dark_Gray='\033[1;30m'
 Red='\033[0;31m'
 Light_Red='\033[1;31m'
 Green='\033[0;32m'
 Light_Green='\033[1;32m'
 Brown_Orange='\033[0;33m'
 Yellow='\033[1;33m'
 Blue='\033[0;34m'
 Light_Blue='\033[1;34m'
 Purple='\033[0;35m'
 Light_Purple='\033[1;35m'
 Cyan='\033[0;36m'
 Light_Cyan='\033[1;36m'
 Light_Gray='\033[0;37m'
 White='\033[1;37m'
 End_Color='\033[0m'

 # Global aliases -- These do not have to be at the beginning of the command line.
 alias -g M='|more'
 alias -g H='|head'
 alias -g T='|tail'
 alias -g P='ps aux'
 alias -g G='|grep'

 alias python3.8="/usr/local/opt/python@3.8/bin/python3"

 alias c="clear"
 alias r="reset"
 alias q="exit"

 alias todo="vim ~/todo.txt"

 alias zconf="vim ~/.zshrc"
 alias zsrc="exec zsh"

 alias omzconf="vim ~/.oh-my-zsh"

 alias vconf="vim ~/.vimrc"

 alias sconf="vim ~/.ssh/config"

 alias tconf="vim ~/.tmux.conf.local"
 alias tsrc=":source-file ~/.tmux.conf"

 alias l="${aliases[ls]} -Ath"
 alias ll="${aliases[l]} -l"

#ZSH aliases
 alias zconf="vim ~/.zshrc"
 alias zsrc="source ~/.zshrc"
 alias omzconf="vim ~/.oh-my-zsh"

#Process aliases
 alias pss="ps aux | grep"

 alias psg="ps aux  | grep -i "
 alias p="python3 "
 alias pi="pip3 install"
 alias cc="cargo check"
 alias ccl="cargo clippy --all-features --all-targets"
 alias ct="cargo test -- --nocapture"
 alias cf="cargo fmt"
 alias cb="cargo build"
 alias cbr="cargo build --release"
 alias rbt1="export RUST_BACKTRACE=1"
 alias rbt0="unset RUST_BACKTRACE"

#Utility
 alias a="atom ."
 alias v="vim"

#Git commands

function cbz() {
     local prev_flags=$(echo $RUSTFLAGS)
     export RUSTFLAGS="-Z macro-backtrace"
     cargo build
     export RUSTFLAGS=$prev_flags
 }

 function startvm() {
     aws ec2 start-instances --instance-ids=$1
 }
 function stopvm() {
     aws ec2 stop-instances --instance-ids=$1
 }

 #function iterm2_print_user_vars() {
 #  iterm2_set_user_var gitBranch $((git branch 2> /dev/null) | grep \* | cut -c3-)
 #}

 function cdc() {
     cd ; code ; $1
 }

 function cx() {
     chmod +x $1
 }


 function gcjb() {
     git clone git@github.com:jacksonbellinger/$1
 }

 function gcrj() {
     git clone git@github.com:redjack/$1
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

 function contains() {
     [[ $1 =~ (^|[[:space:]])$2($|[[:space:]]) ]] && exit(0) || exit(1)
 }

 function list_include_item {
   local list="$1"
   local item="$2"
   if [[ $list =~ (^|[[:space:]])"$item"($|[[:space:]]) ]] ; then
     # yes, list include item
     result=0
   else
     result=1
   fi
   return $result
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

 function grh() {
     git reset --hard HEAD
 }
 function keygen() {
  ssh-keygen -t rsa -b 4096 -C $1
 }

 function fingerprint() {   ssh-keygen -lf $1 -E md5 }

 function pjson() {
     echo "$1" | python -m json.tool
 }

 function uz() {
     if [ ! -f "$1" ] ; then
         echo "'$1' does not exist."
         return 1
     fi

     case "$1" in
         *.tar.bz2)   tar xvjf "$1"   ;;
         *.tar.xz)    tar xvJf "$1"   ;;
         *.tar.gz)    tar xvzf "$1"   ;;
         *.gz)        gunzip "$1"     ;;
         *.tar)       tar xvf "$1"    ;;
         *.tbz2)      tar xvjf "$1"   ;;
         *.tgz)       tar xvzf "$1"   ;;
         *.zip)       unzip "$1"      ;;
         *.Z)         uncompress "$1" ;;
         *.xz)        xz -d "$1"      ;;
         *.a)         ar x "$1"       ;;
         *.rar)       rar x "$1"      ;;
         *.7z)        7z x "$1"       ;;
         *.bz2)       bunzip2 "$1"    ;;
         *)           echo "Unable to extract '$1'." ;;
     esac
 }
