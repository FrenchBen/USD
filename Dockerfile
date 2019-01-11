FROM python:2.7
ARG RELEASE=19.01
RUN apt-get update && apt-get install -y build-essential cmake qt4-qmake qt4-default qt4-dev-tools libqt4-dev lxrandr libxcursor-dev libxinerama-dev libglew-dev
#libgcrypt20-dev zlib1g-dev libxi-dev libxtst-dev0
RUN pip install pyside pyopengl
WORKDIR /pixarusd
RUN curl -sSLO https://github.com/PixarAnimationStudios/USD/archive/v${RELEASE}.tar.gz
RUN tar -zxvf v19.01.tar.gz
WORKDIR /pixarusd/USD-19.01
RUN python --no-image USD-19.01/build_scripts/build_usd.py /usr/local/USD
# Cleanup packages
RUN apt-get remove build-essential cmake qt4-qmake qt4-default qt4-dev-tools libqt4-dev && apt-get clean && rm -rf /var/lib/apt/lists/*
RUN rm -Rf /pixarusd/*
RUN export PYTHONPATH=/usr/local/lib/USD/
RUN export PATH=$PATH:/usr/local/USD/bin

