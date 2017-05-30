#==== Standard Environment ====
#=== Standard file permissions: user:r/w, group: r, others: nothing ===
umask 0027

#=== Environment variables ===
#== Directories ==
export GROUP=$(id -gn) #Group is not set for bash!
export WOODY=/home/woody/$GROUP/$USER
export VAULT=/home/vault/$GROUP/$USER
export HPC=/home/hpc/$GROUP/$USER
export GROUPSHARE=/home/vault/$GROUP/shared
export ECAPSHARE=/home/vault/capshared

############################################################

if [ -f /home/vault/capshared/bashrc ]; then
    source /home/vault/capshared/bashrc
fi

module use -a /home/vault/capm/shared/apps/U16/modulefiles/


############################################################

export
PATH=$PATH:/home/hpc/capm/sn0515/programs/pycharm-community-2016.3.2/bin
alias pycharm='pycharm.sh'

############################################################

module load gnuplot
module load eclipse/neonC++
module load python/2.7-anaconda
module load root/6.08.02
module load scite
module load gcc/6.2.0
