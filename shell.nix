with import <nixpkgs> { };

mkShell {
  nativeBuildInputs = with pkgs; [
    cmake
    ninja
    git

    libGL
    # X11 dependencies
    xorg.libX11
    xorg.libX11.dev
    xorg.libXcursor
    xorg.libXi
    xorg.libXinerama
    xorg.libXrandr
  ];

  shellHook = ''
    echo "Nix shell!"
  '';
}
