# Enable Powerlevel10k instant prompt. Should stay close to the top of ~/.zshrc.
# Initialization code that may require console input (password prompts, [y/n]
# confirmations, etc.) must go above this block; everything else may go below.
if [[ -r "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh" ]]; then
 source "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh"
fi

# Add usr/local, pip user bin, and cargo bin to path
export PATH=$HOME/bin:/usr/local/bin:/$HOME/.local/bin:$HOME/.cargo/bin:$PATH

# Path to your oh-my-zsh installation.
export ZSH="$HOME/.oh-my-zsh"

# Set name of the theme to load --- if set to "random", it will
# load a random theme each time oh-my-zsh is loaded, in which case,
# to know which specific one was loaded, run: echo $RANDOM_THEME
# See https://github.com/robbyrussell/oh-my-zsh/wiki/Themes
#ZSH_THEME="robbyrussell"
ZSH_THEME="powerlevel10k/powerlevel10k"

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
#ENABLE_CORRECTION="true"

# Uncomment the following line to display red dots whilst waiting for completion.
COMPLETION_WAITING_DOTS="true"

# Uncomment the following line if you want to disable marking untracked files
# under VCS as dirty. This makes repository status check for large repositories
# much, much faster.
DISABLE_UNTRACKED_FILES_DIRTY="true"

# Uncomment the following line if you want to change the command execution time
# stamp shown in the history command output.
# You can set one of the optional three formats:
# "mm/dd/yyyy"|"dd.mm.yyyy"|"yyyy-mm-dd"
# or set a custom format using the strftime function format specifications,
# see 'man strftime' for details.
HIST_STAMPS="%Y-%m-%dT%H:%M:%S%:z"

# #Enable command time tracking
# setopt inc_append_history_time

# function preexec() {
#   timer=$(($(date +%s%0N)/1000000))
# }

# function precmd() {
#   if [ $timer ]; then
#     now=$(($(date +%s%0N)/1000000))
#     elapsed=$(($now-$timer))

#     export RPROMPT="%F{cyan}${elapsed}ms %{$reset_color%}"
#     unset timer
#   fi
# }

# Would you like to use another custom folder than $ZSH/custom?
# ZSH_CUSTOM=/path/to/new-custom-folder

# Which plugins would you like to load?
# Standard plugins can be found in ~/.oh-my-zsh/plugins/*
# Custom plugins may be added to ~/.oh-my-zsh/custom/plugins/
# Example format: plugins=(rails git textmate ruby lighthouse)
# Add wisely, as too many plugins slow down shell startup.
MAGIC_ENTER_GIT_COMMAND='_magic_dashboard'
MAGIC_ENTER_OTHER_COMMAND='l'

plugins=(
colored-man-pages
git
npm
rust
systemadmin
web-search
magic-enter
)

source $ZSH/oh-my-zsh.sh

# User configuration

# export MANPATH="/usr/local/man:$MANPATH"

# You may need to manually set your language environment
# export LANG=en_US.UTF-8

# Preferred editor for local and remote sessions
if [[ -n $SSH_CONNECTION ]]; then
    export EDITOR='vim'
else
    export EDITOR='vim'
fi

export LESS="-FX -asrRix8 --mouse --wheel-lines=3"

# Compilation flags
# export ARCHFLAGS="-arch x86_64"

# Set personal aliases, overriding those provided by oh-my-zsh libs,
# plugins, and themes. Aliases can be placed here, though oh-my-zsh
# users are encouraged to define aliases within the ZSH_CUSTOM folder.
# For a full list of active aliases, run `alias`.
#

#TODO write a help function to list all custom functions and their use

function color-palette() {
   for i in {0..255}; do print -Pn "%K{$i}  %k%F{$i}${(l:3::0:)i}%f " ${${(M)$((i%6)):#3}:+$'\n'}; done
}
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

export iso8601_format="%Y-%m-%dT%H:%M:%S%:z"
alias datetime="date +$iso8601_format"
alias unixtime="echo \"$(date -u +'%Y-%m-%dT%H:%M:%SZ')\" | sed 's/Z/.000Z/'"

# Global aliases -- These do not have to be at the beginning of the command line.
alias -g M='|more'
alias -g H='|head'
alias -g T='|tail'
alias -g P='ps aux'
alias -g G='|grep'
#alias -g BG='2>&1 | tee log-$(datetime).out'

alias c="clear"
alias r="reset"
alias q="exit"
alias div="printf '\n%.0s' {1..$LINES}"
alias l="${aliases[ls]} -Ath"
alias ll="${aliases[l]} -l"
alias lls="${aliases[l]} -l | sort -k9,9"

alias psg="psgrep" #https://github.com/ohmyzsh/ohmyzsh/tree/master/plugins/systemadmin#functions

alias zconf="vim ~/.zshrc"
alias zsrc="source ~/.zshrc"
alias omzconf="vim ~/.oh-my-zsh"
alias vconf="vim ~/.vimrc"
alias sconf="vim ~/.ssh/config"
alias tconf="vim ~/.tmux.conf.local"
alias tsrc="source ~/.tmux.conf"

alias todo="vim ~/todo.txt"

if [[ -d ~/.zshfn ]]; then
   # source my function files
   for funcFile in ~/.zshfn/*; do
    #   echo "sourcing $funcFile"
      source $funcFile
   done
fi

function cdc() {
    cd ; code ; $1
}


function magic-enter-cmd {
  last_command=${history[@][1]}
  if [[ "$last_command" == apt* ]]; then
    echo "sudo !!"
  else
    echo "l"
  fi
}

function delete_all_in_except() {
    dirpath="$(realpath $1)"
    foundfiles=$(find $dirpath -mindepth 1 -type f ! -regex ".*/$2.*" -o -type d ! -regex ".*/$2.*")
    #echo "$2(/*?)"
    echo $foundfiles
    #echo "deleting everything in $dirpath except $2/*"
    if test -d "$dirpath" && (test -f "$dirpath/$2" || test -d "$dirpath/$2"); then
        find $dirpath -mindepth 1 -type f ! -regex ".*/$2.*" -delete -o -type d ! -regex ".*/$2.*" -delete
    else
        echo "Invalid args: pass a directory & filename"
        return 1
    fi
}



#function iterm2_print_user_vars() {
#  iterm2_set_user_var gitBranch $((git branch 2> /dev/null) | grep \* | cut -c3-)
#}

function keygen() {
    ssh-keygen -t ed25519 -b 4096 -C $1
}

function fingerprint() {
    ssh-keygen -lf $1 -E md5
}

function pjson() {
    echo "$1" | python -m json.tool
}

function ffmpeg_c() {
    local encoding_lib=""
    case $2 in
        "webp")
             encoding_lib="libwebp";;
        "avif")
            encoding_lib="libaom-av1 -still-picture 1";;
        *)
              echo "unsupported encoding";;
    esac
    echo "$encoding_lib: ${1%.*}.$2"
    ffmpeg -i $1  -c:v $encoding_lib ${1%.*}.$2
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

# To customize prompt, run `p10k configure` or edit ~/.p10k.zsh.
[[ ! -f ~/.p10k.zsh ]] || source ~/.p10k.zsh

export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion
