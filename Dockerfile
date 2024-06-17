FROM eldipa/sercom-student-ubuntu

RUN sudo apt-get update && \
  sudo apt install -y \
  libsdl2-dev \
  libsdl2-image-dev \
  libsdl2-ttf-dev \
  libsdl2-mixer-dev \
  libyaml-cpp-dev \
  x11-apps

ENV DISPLAY :0

WORKDIR /tp-final-veiga

COPY . .

RUN ./build.sh
