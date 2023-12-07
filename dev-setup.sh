#!/bin/bash
set -x
sudo apt upgrade && sudo apt -y update

#General
sudo apt install -y git net-tools rsync

#Shell
sudo apt install -y zsh
#get nerdfont patched mononoki & firacode
curl -OL https://github.com/ryanoasis/nerd-fonts/releases/latest/download/Mononoki.tar.xz
tar -xf Mononoki.tar.xz -C ~/.local/share/fonts
rm Mononoki.tar.xz
curl -OL https://github.com/ryanoasis/nerd-fonts/releases/download/v3.0.2/FiraCode.tar.xz
tar -xf FiraCode.tar.xz -C ~/.local/share/fonts
rm FiraCode.tar.xz


#install oh my zsh
sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
#install powerlevel10k
git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/themes/powerlevel10k
local dotfiles_dir = $(pwd)
#copy zsh and p10k configs
ln -s $dotfiles_dir/.zshrc ~/.zshrc
ln -s $dotfiles_dir/.vimrc ~/.vimrc
ln -s $dotfiles_dir/.gitconfig ~/.gitconfig
ln -s $dotfiles_dir/.p10k.zsh ~/.p10k.zsh
source ~/.zshrc

#Images
sudo apt install -y ffmpeg

#Python
sudo apt install -y python3
sudo apt install -y python3-pip
sudo -H python3 -m pip install --upgrade pip
pip3 install numpy
pip3 install pandas
pip3 install matplotlib

#Rust
curl https://sh.rustup.rs -sSf | sh -s -- -y
reset

cargo install cargo-audit
cargo install eza

#Webdev
sudo apt install -y nodejs npm
