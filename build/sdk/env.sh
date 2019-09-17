groupmod -g ${GROUP_ID} developer
usermod -u ${USER_ID} -g ${GROUP_ID} developer
export DISPLAY=$DISPLAY
export SSH_AUTH_SOCK=$SSH_AUTH_SOCK
export SRC_DIR=$SRC_DIR
export wt_DIR=$wt_DIR
export INSTALL_DIR=$INSTALL_DIR
su -w DISPLAY -w SSH_AUTH_SOCK -w SRC_DIR -w wt_DIR -w INSTALL_DIR -l developer /sdk/$@