#!/usr/bin/env zsh
# Based on Magic-Enter by @dufferzafar (MIT License)
# https://github.com/ohmyzsh/ohmyzsh/tree/master/plugins/magic-enter
# modified to limit lines and columns to fit in terminal size, and to colorize git status
# draws a separator line with terminal width
function _separator {
	local truncate_n=$1
	let width=COLUMNS-truncate_n
	local sep_char="═" # ─ ═
	local sep=""
	for ((i = 0; i < width; i++)); do
		sep="$sep$sep_char"
	done
	print "\033[1;30m$sep\033[0m"
}

function _gitlog {
	local max_log_lines=$1
	# echo "log has $max_log_lines lines"
	# shellcheck disable=2086
	let max_branch_width="$COLUMNS * .2"
	x=${max_branch_width%.*}
	# echo "branch $x"
	# echo "branch $max_branch_width"

	let max_commit_width="$COLUMNS+15"
	max_commit_width=${max_commit_width%.*}
	# echo "commit $max_commit_width"
	# echo $COLUMNS
	#%<(50,trunc)%s
	git log --all --color \
		--format="%C(yellow)%h%C(red)%d%C(reset) %s %C(bold blue)%an%C(reset)" -n $max_log_lines |
	sed -e 's/grafted/ /' \
		-e 's/origin\//󰞶 /g' \
		-e 's/upstream\// /g' \
		-e 's/HEAD/󱍞/g' \
		-e 's/tag: / /' \
		-e 's/\* /∘/' \
		-Ee $'s/ (improv|fix|refactor|build|ci|docs|feat|test|perf|chore|revert|break|style)(\\(.+\\)|!)?:/ \033[1;35m\\1\033[1;36m\\2\033[0m:/' \
		-Ee $'s/ (fixup|squash)!/\033[1;32m&\033[0m/g' \
		-Ee $'s/`[^`]*`/\033[1;36m&\033[0m/g' \
		-Ee $'s/#[0-9]+/\033[1;31m&\033[0m/g' \
		-re "s/[(]([^)]{0,$x})[^)]*[)]/\(\1\)/g" \
		-re s"/(.{0,$max_commit_width}).*/\1/"
		# -re "s/([^(]{0,$x})[^)]*/)\1/g"
		# -e "s/[(][^)]*[)]/()/g" \
		# -e "s/\)([^)]{0,$max_commit_width}).*/)\1/"p

	# awk -F ")" -v w="$max_col_width" 'BEGIN { OFS=FS }; { $1=substr($1, 1, w); print }' | tee >(
	# awk -F '\(.*\)' -v w="$max_col_width" 'BEGIN { OFS=FS }; { $2=substr($2, 1, w); print }' )
	# INFO inserting ansi colors via sed requires leading $
	# -e $"s/([^\)]\\{$mac_col_width\\})[^\)]*/\\1/g"
	#-e $'s/\)\\(.*?\\)\\(\(\d\w\)\\)/\)\\1aaaa\\2\(/'
}

function _gitstatus {
	local max_status_lines=$1
	max_status_lines=${max_status_lines%.*}
	# echo "status has $max_status_lines lines"
	# so new files show up in `git diff`
	git ls-files --others --exclude-standard | xargs git add --intent-to-add &>/dev/null

	if [[ -n "$(git status --porcelain)" ]]; then
		local unstaged staged
		unstaged=$(git diff --color="always" --compact-summary --stat=$COLUMNS | sed -e '$d' \
		-e "s/^[ \t]*//" \
		-re "s/^([^ ]*)/$(printf '\033[0;31m')\\1$(printf '\033[0m')/") #Strip leading whitespace & color red

		staged=$(git diff --staged --color="always" --compact-summary --stat=$COLUMNS | sed -e '$d' \
			-e "s/^[ \t]*//" \
			-re "s/^([^ ]*)/$(printf '\033[0;32m')\\1$(printf '\033[0m')/" \
			-e $'s/^ /+/' ) # add marker for staged files
		local diffs
		if [[ -n "$unstaged" && -n "$staged" ]]; then
			diffs="$staged\n$unstaged"
		elif [[ -n "$unstaged" ]]; then
			diffs="$unstaged"
		elif [[ -n "$staged" ]]; then
			diffs="$staged"
		fi
		local status_output
		local overflow
		status_output=$(print "$diffs" | sed \
			-e $'s/\\(gone\\)/\033[1;31mD\033[0m/g' \
			-e $'s/\\(new\\)/\033[1;32mN\033[0m/g' \
			-e 's/ Bin //g' \
			-Ee $'s|([^/+]*)(/)|\033[1;36m\\1\033[1;33m\\2\033[0m|g' \
			-e $'s/^\\+/\033[1;35m \033[0m/')

		# gs_out=$(git status | sed \
		# -e "s/Changes to be committed://" \
		# -e "s/  (use "git restore --staged <file>..." to unstage)//" \
		# -e "s/Changes to be committed://" \
		# -e "s/Changes to be committed://" \
		# -e "s/Changes to be committed://")
			# -e $'s/ \\| Unmerged /\033[1;31m \033[0m/'\
		# if [[ $(echo "$status_output" | wc -l) -gt $max_status_lines ]]; then
		# 	local shortened
		# 	shortened="$(echo "$status_output" | head -n"$max_status_lines")"
		# 	printf "%s\033[1;36m(…)\033[0m" "$shortened"
		# 	overflow=4
		# elif [[ -n "$status_output" ]]; then
			echo "$status_output"
		# fi
		_separator
	fi
}

function _list_files_here {
	local max_ls_lines=$1
	max_ls_lines=${max_ls_lines%.*}
	# echo "list has $max_ls_lines lines"
	if [[ ! -x "$(command -v eza)" ]]; then print "\033[1;33mMagic Dashboard: \`eza\` not installed.\033[0m" && return 1; fi

	local eza_output
	eza_output=$(eza --width="$COLUMNS" --all --grid --color=always --icons \
		--git-ignore --ignore-glob=".DS_Store|Icon?" \
		--sort=name --group-directories-first --no-quotes \
		--git --long --no-user --no-permissions --no-filesize --no-time)

	if [[ $(echo "$eza_output" | wc -l) -gt $max_ls_lines ]]; then
		local shortened
		shortened="$(echo "$eza_output" | head -n"$max_ls_lines")"
		printf "%s \033[1;36m(…)\033[0m" "$shortened"
	elif [[ -n "$eza_output" ]]; then
		echo "$eza_output"
	fi
}

#───────────────────────────────────────────────────────────────────────────────

# show files + git status + brief git log
function _magic_dashboard {
	# check if pwd still exists
	if [[ ! -d "$PWD" ]]; then
		printf '\033[1;33m"%s" has been moved or deleted.\033[0m\n' "$(basename "$PWD")"
		if [[ -d "$OLDPWD" ]] ; then
			print '\033[1;33mMoving to last directory.\033[0m'
			# shellcheck disable=2164
			cd "$OLDPWD"
		fi
		return 0
	fi
	#$((JOBS>4 ? JOBS : 4))
	let log_lines="($LINES*.4)-1"
	let status_lines="$LINES*.4"
	let ls_lines="$LINES*.2"
	if git rev-parse --is-inside-work-tree &>/dev/null; then
		_gitlog $log_lines
		_separator
		_gitstatus $status_lines
	fi
	_list_files_here $ls_lines
}

#───────────────────────────────────────────────────────────────────────────────

function _magic_enter {
	# GUARD only in PS1 and when BUFFER is empty
	# DOCS http://zsh.sourceforge.net/Doc/Release/Zsh-Line-Editor.html#User_002dDefined-Widgets
	[[ -z "$BUFFER" && "$CONTEXT" == "start" ]] || return 0

	# GUARD only when in terminal with sufficient height
	local disabled_below_height=${MAGIC_DASHBOARD_DISABLED_BELOW_TERM_HEIGHT:-15}
	[[ $LINES -gt $disabled_below_height ]] || return 0

	echo && _magic_dashboard
}

# WRAPPER FOR THE ACCEPT-LINE ZLE WIDGET (RUN WHEN PRESSING ENTER)
# If the wrapper already exists don't redefine it
type _magic_enter_accept_line &>/dev/null && return

# WARN running the `shfmt` on this section will break it
# shellcheck disable=2154
case "${widgets[accept-line]}" in
		# Override the current accept-line widget, calling the old one
	user:*) zle -N _magic_enter_orig_accept_line "${widgets[accept-line]#user:}"
		function _magic_enter_accept_line {
			_magic_enter
			zle _magic_enter_orig_accept_line -- "$@"
		} ;;

		# If no user widget defined, call the original accept-line widget
	builtin) function _magic_enter_accept_line {
			_magic_enter
			zle .accept-line
		} ;;
esac

# zle -N accept-line _magic_enter_accept_line