sudo apt upgrade && sudo apt -y update

#General
sudo apt install -y git net-tools rsync

#Shell
sudo apt install -y zsh
#install oh my zsh
sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
#install powerlevel10k
git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/themes/powerlevel10k
#copy zsh and p10k configs
cp ./.zshrc ~/
cp ./.p10k.zsh ~/
cp ./.vimrc ~/
cp ./.gitconfig ~/
git config core.filemode true
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

#Webdev
sudo apt install -y nodejs npm
