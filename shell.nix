with import <nixpkgs> { };

mkShell {
  nativeBuildInputs = with pkgs; [
    SDL2
    SDL2_image
    pcre2
    freetype
    glew
    glm
    glfw
    boost
    cmake
    libpng
    libGL
    libwebp
    libtiff
    xorg.libX11
  ];

  shellHook = ''
    echo "Nix shell!"
  '';
}
