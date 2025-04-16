with import <nixpkgs> { };

mkShell {
  nativeBuildInputs = with pkgs; [
    SDL2
    SDL2_image
    pcre2
    freetype
    glew
    glm
    boost
    libpng
    libwebp
    libtiff
  ];

  shellHook = ''
    echo "Nix shell!"
  '';
}
