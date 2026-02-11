# Homebrew Formula for obsidian-pub
class ObsidianPub < Formula
  include Language::Python::Virtualenv

  desc "Command-line tool for managing Obsidian markdown notes with git"
  homepage "https://github.com/professoroakz/obsidian-pub"
  url "https://github.com/professoroakz/obsidian-pub/archive/v0.1.0.tar.gz"
  sha256 "PLACEHOLDER_SHA256_WILL_BE_CALCULATED"
  license "MIT"
  head "https://github.com/professoroakz/obsidian-pub.git", branch: "main"

  depends_on "python@3.11"
  depends_on "git"

  def install
    virtualenv_install_with_resources
    
    # Install scripts
    bin.install Dir["scripts/*.sh"]
    
    # Install Makefile
    prefix.install "Makefile"
    
    # Create wrapper script
    (bin/"obsidian-pub").write_env_script(
      libexec/"bin/obsidian-pub",
      PATH: "#{libexec}/bin:$PATH"
    )
  end

  test do
    system "#{bin}/obsidian-pub", "--version"
    assert_match "obsidian-pub", shell_output("#{bin}/obsidian-pub --help")
  end
end
